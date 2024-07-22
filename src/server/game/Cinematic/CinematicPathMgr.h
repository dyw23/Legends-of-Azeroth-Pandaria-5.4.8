/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
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

#ifndef _CINEMATIC_SEQUENCE_MGR
#define _CINEMATIC_SEQUENCE_MGR

#include "Common.h"
#include "Config.h"
#include "Object.h"

/// Cinematic sequence key frame
struct CinematicKeyFrame
{
    uint32 Frame;
    float Position[3];
};

/// Cinematic sequence
class CinematicSequence
{
public:
    /// Constructor
    CinematicSequence();
    /// Destructor
    ~CinematicSequence();

    /// Get position at time
    void GetPositionAtTime(uint32 p_Time, float * p_X, float * p_Y, float * p_Z) const;

    /// Sequence durations
    uint32 Duration;
    /// Key Frame count
    size_t KeyFramesCount;
    /// Key frames
    CinematicKeyFrame* KeyFrames;
};

/// Cinematic sequence Mgr
class CinematicSequenceMgr
{
    /// Constructor
    CinematicSequenceMgr();
    /// Destructor
    ~CinematicSequenceMgr();

public:
    static CinematicSequenceMgr* instance();
    /// Load all sequence
    size_t Load();

    /// Get a sequence by his id
    CinematicSequence const* GetSequence(uint32 p_SequenceID);

private:
    std::map<uint32, CinematicSequence*> m_Sequences;
};

#define sCinematicSequenceMgr CinematicSequenceMgr::instance()

#endif /* CINEMATIC_SEQUENCE_MGR */
