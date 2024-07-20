/*
* This file is part of the Legends of Azeroth Pandaria Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QueryPackets_h__
#define QueryPackets_h__

#include "Packet.h"
#include "ObjectGuid.h"
#include "SharedDefines.h"

namespace WorldPackets
{
    namespace Query
    {
        class QueryGameObject final : public ClientPacket
        {
        public:
            QueryGameObject(WorldPacket&& packet) : ClientPacket(CMSG_GAMEOBJECT_QUERY, std::move(packet)) { }

            void Read() override;

            ObjectGuid Guid;
            uint32 GameObjectID = 0;
        };

        struct GameObjectStats
        {
            std::string Name[4];
            std::string IconName;
            std::string CastBarCaption;
            std::string UnkString;
            uint32 Type = 0;
            uint32 DisplayID = 0;
            std::array<uint32, MAX_GAMEOBJECT_DATA> Data = { };
            float Size = 0.0f;
            std::vector<uint32> QuestItems;
            uint32 UnkInt32 = 0;

            size_t GetDataSize() const
            {
                //                                         [1..3] always empty '\0'                     '\0'                          '\0'                     '\0'                                 QuestItems counter
                return sizeof(Type) + sizeof(DisplayID) + (Name->size() + (4 * 1)) + (IconName.size() + 1) + (CastBarCaption.size() + 1) + (UnkString.size() + 1) + sizeof(Data) + sizeof(Size) + sizeof(uint8) + (QuestItems.size() * sizeof(uint32)) + sizeof(UnkInt32);
            }
        };

        class QueryGameObjectResponse final : public ServerPacket
        {
        public:
            QueryGameObjectResponse() : ServerPacket(SMSG_GAMEOBJECT_QUERY_RESPONSE, 165) { }

            WorldPacket const* Write() override;

            uint32 GameObjectID = 0;
            bool Allow = false;
            GameObjectStats Stats;
        };
    }
}

#endif