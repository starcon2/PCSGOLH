# PCSGOLH ![](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg) ![](https://img.shields.io/badge/game-CS%3AGO-yellow.svg) ![](https://img.shields.io/badge/platform-Windows-0078d7.svg) ![](https://img.shields.io/badge/arch-x86-red.svg) ![](https://img.shields.io/badge/license-MIT-blue.svg) [![Build status](https://ci.appveyor.com/api/projects/status/muby87gajywws5yj?svg=true)](https://ci.appveyor.com/project/xrivendell/pcsgolh)


PCSGOLH - Pointless Counter-Strike: Global Offensive Lua Hooks. A open-source Lua API for CS:GO hacking written in modern C++

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
*(Documentation still not finished)*

### Prerequisites

```
Visual Studio 2013+
```
### Building

Open up a project, make sure that build mode is set to **Release**, click build. Now the compiler should build all the required libraries and then the main project.
Default script location is not defined, to change it to whatever you want, head to `sdk/sdk.hpp` and change the `SCRIPT_DIR`.

### Usage

If you already sucessfully build project, head to Release folder where you should find `Injector.exe` and `PCSGOLH.dll`. Open a console there and type `Injector.exe <dir to your project>/Release/PCSGOLH.dll`. Make sure that Counter-Strike Global Offensive is **running** if not injector will throw an error.

### Injector

DLL Injection works by tricking/forcing the target process into loading a DLL of your choice. After that, the code in that DLL will get executed as part of the target process and will be able to do anything the process itself can.
Usage of included injector: `Injector.exe <dir to .dll>`

### Example

Simple esp boxes
```lua
_Engine = Interfaces:GetEngine()
_EntityList = Interfaces:GetEntityList()

function DrawBox(pEntity)
	local vEyePos = pEntity:GetEyePos()
	local vOrigin = pEntity:GetAbsOrigin()
	
	local vHeadScreen = Vector()
	local vOrigScreen = Vector()
	
	Utils:WorldToScreen(vEyePos, vHeadScreen)
	Utils:WorldToScreen(vOrigin, vOrigScreen)
	
	local iBoxHeight = math.abs(vHeadScreen.Y - vOrigScreen.Y)
	local iBoxWidth = iBoxHeight / 1.8
	
	DrawManager:DrawRect(vHeadScreen.X - iBoxWidth / 2, vHeadScreen.Y, iBoxWidth, iBoxHeight, 255, 0, 255, 255)
end

function OnPaint(panel)
	if _Engine:IsInGame() then
		local pLocal = _EntityList:GetEntityFromIndex(_Engine:GetLocalPlayer())
		
		if not pLocal:IsValid() then return end
		
		for i = 1, _EntityList:GetHighestEntityIndex() do
			local pEntity = _EntityList:GetEntityFromIndex(i)
			if pEntity:IsValid() then
				if pEntity:GetClassId() == 38 then
					if pEntity:IsAlive()
						and not pEntity:IsDormant()
						and i ~= _Engine:GetLocalPlayer() then
						DrawBox(pEntity)
					end
				end
			end
		end
	end
end
Hooks:Register(HOOK_PAINTTRAVERSE, OnPaint)
```
For more examples check [examples](https://github.com/xrivendell/PCSGOLH/tree/master/examples)

## Built With

* [Boost](https://github.com/boostorg/boost) - LuaBind required utilities.
* [Lua](https://github.com/lua/lua) - Programming language.
* [LuaBind](https://github.com/luabind/luabind) - Binding C++ functions to lua.

## FAQ

- **My script crashes without throwing any errors**
	- Make sure that your syntax is right, im working on this.

## Authors

* **Sebastian Lyko** - *Initial work* - [xrivendell](https://github.com/xrivendell)

See also the list of [contributors](https://github.com/xrivendell/PCSGOLH/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details