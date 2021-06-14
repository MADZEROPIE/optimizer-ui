/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      problem_manager.cpp                                         //
//                                                                         //
//  Purpose:   Source file for dynamic libraries manager class             //
//                                                                         //
//                                                                         //
//  Author(s): Sovrasov V.                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "problem_manager.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
TProblemManager::TProblemManager() : mLibHandle(NULL), mProblem(NULL),
  mCreate(NULL), mDestroy(NULL)
{

}

// ------------------------------------------------------------------------------------------------
TProblemManager::~TProblemManager()
{
  FreeProblemLibrary();
}

// ------------------------------------------------------------------------------------------------
int TProblemManager::LoadProblemLibrary(const std::string& libPath)
{
  if (mLibHandle)
    FreeProblemLibrary();
  mLibHandle = LoadLibrary(libPath.c_str());

  if (!mLibHandle)
  {
    std::cerr << "Cannot load library: " << libPath << std::endl;
    return TProblemManager::ERROR_;
  }
  mCreate = (create_t*)GetProcAddress(mLibHandle, "create");
  mDestroy = (destroy_t*)GetProcAddress(mLibHandle, "destroy");
  if (!mCreate || !mDestroy)
  {
    std::cerr << "Cannot load symbols: " << GetLastError() << std::endl;
    FreeLibHandler();
    return TProblemManager::ERROR_;
  }

  mProblem = mCreate();
  if (!mProblem)
  {
    FreeLibHandler();
    mCreate = NULL;
    mDestroy = NULL;
    std::cerr << "Cannot create problem instance" << std::endl;
  }

  return TProblemManager::OK_;
}

// ------------------------------------------------------------------------------------------------
void TProblemManager::FreeLibHandler()
{
  FreeLibrary(mLibHandle);
  mLibHandle = NULL;
}

// ------------------------------------------------------------------------------------------------
int TProblemManager::FreeProblemLibrary()
{
  if (mProblem)
    mDestroy(mProblem);
  if (mLibHandle)
    FreeLibHandler();
  mLibHandle = NULL;
  mProblem = NULL;
  mCreate = NULL;
  mDestroy = NULL;
  return TProblemManager::OK_;
}

// ------------------------------------------------------------------------------------------------
IProblem* TProblemManager::GetProblem() const
{
  if (mProblem)
    return mProblem;
  else
    return NULL;
}
// - end of file ----------------------------------------------------------------------------------