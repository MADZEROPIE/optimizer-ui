﻿/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      problem_manager.h                                           //
//                                                                         //
//  Purpose:   Header file for dynamic libraries manager class             //
//                                                                         //
//                                                                         //
//  Author(s): Sovrasov V.                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

/**
\file problem_manager.h

\authors Соврасов В.
\date 2016
\copyright ННГУ им. Н.И. Лобачевского

\brief Объявление класса #TProblemManager

*/

#ifndef __PROBLEMMANAGER_H__
#define __PROBLEMMANAGER_H__

#include "problem_interface.h"
#include "OptimizerCoreGlobal.hpp"
#include <string>

#include <direct.h>
#include <windows.h>

/**
Класс, реализующий загрузку и выгрузку подключамеых библиотек с задачами

В классе #TProblemManager реализованы основные функции, для загрузки\выгрузки библиотек с задачами
*/
class EXPORT_API TProblemManager {
protected:
    ///Указатель на дескриптор загруженной библиотеки
    HINSTANCE mLibHandle;
    ///Указатель на созданный объект, описывающий задачу
    IProblem* mProblem;
    ///Указатель на функцию-фабрику задач
    create_t* mCreate;
    ///Указатель на функцию-деструктор задач
    destroy_t* mDestroy;

    /// Метод, освобождающий загруженную библиотеку. Будет вызван в деструкторе
    int FreeProblemLibrary();

    ///Служебный метод, освобождающий #mLibHandle
    void FreeLibHandler();

public:
    /**
    Код ошибки, возвращаемый методами #LoadProblemLibrary и #FreeProblemLibrary
    при успешном выполнении операций
    */
    static const int OK_ = 0;
    /**
    Код ошибки, возвращаемый методами #LoadProblemLibrary и #FreeProblemLibrary
    при ошибке во время выполнении операций
    */
    static const int ERROR_ = -2;

    ///Конструктор
    TProblemManager();
    ///Деструктор, в нём вызывается #FreeProblemLibrary
    ~TProblemManager();

    /** Метод, загружающий библиотеку, находящуюся по указанному пути

    Метод загружает библиотеку, пытается импортировать из неё функции,
    создающие и уничтожающие задачу, а затем создаёт задачу

    \param[in] libPath Путь к загружаемой библиотеке
    \return Код ошибки
    */
    int LoadProblemLibrary(const std::string& libPath);

    /** Метод возвращает указатель #mProblem
     */
    IProblem* GetProblem() const;
};

#endif
// - end of file ----------------------------------------------------------------------------------