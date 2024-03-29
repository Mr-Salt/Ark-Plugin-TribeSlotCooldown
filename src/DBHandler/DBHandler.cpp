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
* \file DBHandler.cpp
* \author Matthias Birnthaler Matthias.Birnthaler@outlook.com
* \date 15 May 2019
* \brief Interface to the database
*
*/


/* ================================================[includes]================================================ */

#include "DBHandler.h"
#include "API/ARK/Ark.h"


/* =====================================[class DBHandler implementation]===================================== */

/**
* \brief Constructor of the DB Handler
*
* This initialisation of the database
*
* \param[in] path string the the database, if empty the default path will get used
*/
DBHandler::DBHandler(const std::string& path) : mdb(path.empty() ? ArkApi::Tools::GetCurrentDir() + "/ArkApi/Plugins/TribeSlotCooldown/Slots.db" : path)
{        

    try
    {
        mdb << "PRAGMA journal_mode=WAL;";

        mdb << "create table if not exists TribeSlots ("
               "TribeId integer primary key autoincrement not null,"
               "SlotsTimer BLOB"
               ");";
    }
    catch (const std::exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
    }
};



/**
* \brief Add tribe to database
*
* Interface to add a tribeid to the database
*
* \param[in] TribeId the tribe id to add
* \return void
*/
void DBHandler::AddTribe(const int TribeId)
{
    try
    {
        mdb << "INSERT INTO TribeSlots VALUES (?,?)" << TribeId << 0;
    }
    catch (const sqlite::sqlite_exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
    }
};



/**
* \brief Get tribe slots timer
*
* Interface to select the slots cooldowns of a given tribe
*
* \param[in] TribeId the tribe to look for 
* \return std::vector<int> vector cooldown times
*/
std::vector<int> DBHandler::GetTribeSlotsTimer(const int TribeId)
{

    std::vector<int> slots;

    try
    {
        mdb << "SELECT SlotsTimer from TribeSlots where TribeId = ?;" << TribeId >> slots;
    }
    catch (const sqlite::sqlite_exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
    }

    return slots;
}


/**
* \brief Update slots cooldown
*
* Interface to update the slots cooldown of a given tribe
*
* \param[in] TribeId the tribe id
* \param[in] SlotTimer vector with the cooldown slots
* \return bool true, if update was possible, otherwise false
*/
bool DBHandler::UpdateSlotTimer(const int TribeId, const std::vector<int> SlotTimer)
{
    try
    {
        mdb << "UPDATE TribeSlots SET SlotsTimer = ? WHERE TribeId = ?;" << SlotTimer << TribeId;
        return true;
    }
    catch (const sqlite::sqlite_exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
        return false;
    }
}


/**
* \brief Checks if tribe is in database
*
* Interface to check if a given tribe is in the database
*
* \param[in] TribeId the tribe id to look for
* \return bool true if the tribe is in the database, otherwise false
*/
bool  DBHandler::IsTribeInDatabase(int TribeId)
{
    int count = 0;
    bool result = false;

    try 
    {
        mdb << "SELECT count(1) FROM TribeSlots WHERE TribeId = ?;" << TribeId >> count;
    }
    catch (const sqlite::sqlite_exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());
        return false;
    }

    if (count != 0)
    {
        result = true;
    }


    return result;
}


/**
* \brief Delete tribe 
*
* Interface to delete a given Tribe in the database
*
* \param[in] TribeId the tribe id to look for
* \return bool true if the tribe is in the database, otherwise false
*/
void  DBHandler::DeleteTribe(int TribeId)
{
    try
    {
        mdb << "DELETE FROM TribeSlots WHERE TribeId = ?;" << TribeId;
    }
    catch (const sqlite::sqlite_exception& exception)
    {
        Log::GetLog()->error("({} {}) Unexpected DB error {}", __FILE__, __FUNCTION__, exception.what());

    }
}

/* =================================================[end of file]================================================= */
