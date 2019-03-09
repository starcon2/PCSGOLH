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