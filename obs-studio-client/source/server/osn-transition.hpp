/******************************************************************************
    Copyright (C) 2016-2019 by Streamlabs (General Workings Inc)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#pragma once
#include "osn-source.hpp"

namespace obs
{
	class Transition : public obs::Source
	{
		public:
		// Function
		static std::vector<std::string> Types();
		static uint64_t Create(std::string sourceId, std::string name, std::string settingsData);
		static uint64_t CreatePrivate(std::string sourceId, std::string name, std::string settingsData);
		static uint64_t FromName(std::string name);

		// Method
		static std::pair<uint64_t, uint32_t> GetActiveSource(uint64_t sourceId);
		static void Clear(uint64_t sourceId);
		static void Set(uint64_t transitionId, uint64_t sourceId);
		static bool Start(uint64_t transitionId, uint32_t ms, uint64_t sourceId);
	};
}