#pragma once

#define SCRIPT_DIR "X:\\change\\me\\please\\script.lua"

// others
#include "utils.hpp"
#include "vmt.hpp"
#include "color.hpp"
#include "events.h"

#include "luastate.hpp"
#include "logger.hpp"

// math
#include "vector.h"
#include "qangle.h"

// interfaces
#include "ibaseclient.hpp"
#include "isurface.hpp"
#include "iengine.hpp"

// classes
#include "cpanel.hpp"
#include "cglobalvars.hpp"
#include "cusercmd.hpp"
#include "cbaseentity.hpp"
#include "ccliententitylist.hpp"

#define	FL_ONGROUND					(1 << 0)
#define FL_DUCKING					(1 << 1)

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)
#define IN_SPEED					(1 << 17)
#define IN_WALK						(1 << 18)
#define IN_ZOOM						(1 << 19)
#define IN_WEAPON1					(1 << 20)
#define IN_WEAPON2					(1 << 21)
#define IN_BULLRUSH					(1 << 22)
#define IN_GRENADE1					(1 << 23)
#define IN_GRENADE2					(1 << 24)
#define	IN_ATTACK3					(1 << 25)
