/*****************************************************************************************************************
* Copyright (C) 2019 by Matthias Birnthaler                                                                      *
*                                                                                                                *
* This file is part of the TribeSlotCooldown Plugin for Ark Server API                                           *
*                                                                                                                *
*    This program is free software : you can redistribute it and/or modify                                       *
*    it under the terms of the GNU General Public License as published by                                        *
*    the Free Software Foundation, either version 3 of the License, or                                           *
*    (at your option) any later version.                                                                         *
*                                                                                                                *
*    This program is distributed in the hope that it will be useful,                                             *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of                                              *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                                                 *
*    GNU General Public License for more details.                                                                *
*                                                                                                                *
*    You should have received a copy of the GNU General Public License                                           *
*    along with this program.If not, see <https://www.gnu.org/licenses/>.                                        *
*                                                                                                                *
*****************************************************************************************************************/


/**
* \file TribeSlotCooldown.cpp
* \author Matthias Birnthaler Matthias.Birnthaler@outlook.com
* \date 15 May 2019
* \brief Implementation of DLLMain
*
*/

/* ================================================ [includes] ================================================ */

#include "TribeSlotCooldown.h"
#include "SlotCooldown.h"
#include "Commands.h"

/* ===================================== [prototype of local functions] ======================================= */

static void Load(void);
static void Unload(void);


/* ===================================== [definition of local functions] ====================================== */

/**
* \brief Load of TribeSlotCooldown Plugin
*
* \brief This function loads the Plugin and calls the initialisation
*
* \return void
*/
static void Load(void)
{
    Log::Get().Init("TribeSlotCooldown");

    SlotCooldown::InitSlotCooldown();
    Commands::InitCommands();
    InitHooks();
}


/**
* \brief Unload of TribeSlotCooldown Plugin
*
* This function unloads the Plugin
*
* \return void
*/
static void Unload(void)
{
    RemoveHooks();
    Commands::RemoveComands();
}


/* ===================================== [definition of global functions] ===================================== */

/**
* \brief DLLMain of the TribeSlotCooldown Plugin
*
* \param[in] hModule
* \param[in] ul_reason_for_call
* \param[in] lpReserved
* \return BOOL
*/
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Load();
        break;
    case DLL_PROCESS_DETACH:
        Unload();
        break;
    }
    return TRUE;
}

/* =================================================[end of file]================================================= */
