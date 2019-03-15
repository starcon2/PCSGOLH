_Engine = Interfaces:GetEngine()
_EntityList = Interfaces:GetEntityList()

_Screen = _Engine:GetScreenSize()

function DrawRadarBackground()
	local iCenterX = 300
	local iCenterY = 300
	local iSize = 100
	local x = _Screen.Width / 2
	local y = _Screen.Height / 2
		
	DrawManager:DrawFilledRect(iCenterX - iSize, iCenterY - iSize, 2 * iSize + 2, 2 * iSize + 2, 30, 30, 30, 60)
	DrawManager:DrawFilledRect(iCenterX, iCenterY - iSize, 1, 2 * iSize, 0,255,0,60)
	DrawManager:DrawFilledRect(iCenterX - iSize, iCenterY, 2 * iSize, 1, 0,255,0,60)
end

function DrawRadarPoint(vOriginX, vOriginY, qAngle)
	local flDeltaX = vOriginX.X - vOriginY.X
	local flDeltaY = vOriginX.Y - vOriginY.Y

	local flAngle = qAngle.Y

	local flYaw = (flAngle)* (3.14159265358979323846 / 180.0)
	local flMainViewAngles_CosYaw = math.cos(flYaw)
	local flMainViewAngles_SinYaw = math.sin(flYaw)

	local x = flDeltaY * (-flMainViewAngles_CosYaw) + flDeltaX * flMainViewAngles_SinYaw
	local y = flDeltaX * (-flMainViewAngles_CosYaw) - flDeltaY * flMainViewAngles_SinYaw

	local flRange = 2000

	if math.abs(x) > flRange and math.abs(y) > flRange then
		if y > x then
			if y > -x then
				x = flRange * x / y
				y = flRange
			 else
				y = -flRange * y / x
				x = -flRange
			 end
		else
			 if y > -x then
				y = flRange * y / x
				x = flRange
			 else
				x = -flRange * x / y
				y = -flRange
			 end
		end
	end

	local iScreenX = 300 + (x / flRange * 100)
	local iScreenY = 300 + (y / flRange * 100)

	DrawManager:DrawRect(iScreenX - 3, iScreenY - 3, 7, 7, 0, 0, 0, 255)
	DrawManager:DrawFilledRect(iScreenX - 2, iScreenY - 2, 5, 5, 255, 0, 0, 255)
end

function OnPaint(panel)
	if _Engine:IsInGame() then
		local pLocal = _EntityList:GetEntityFromIndex(_Engine:GetLocalPlayer())
		
		if not pLocal:IsValid() then return end
		
		DrawRadarBackground()
		
		local vAngles = pLocal:GetAbsAngles()
		
		for i = 1, _EntityList:GetHighestEntityIndex() do
			local pEntity = _EntityList:GetEntityFromIndex(i)
			if pEntity:IsValid() then
				if pEntity:GetClassId() == 38 then
					if pEntity:IsAlive() and not pEntity:IsDormant() and i ~= _Engine:GetLocalPlayer() then
						DrawRadarPoint(pEntity:GetAbsOrigin(), pLocal:GetAbsOrigin(), vAngles)
					end
				end
			end
		end
	end
end
Hooks:Register(HOOK_PAINTTRAVERSE, OnPaint)