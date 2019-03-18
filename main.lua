
-- important/main vars
pEngine = Interfaces:GetEngine()
pEntityList = Interfaces:GetEntityList()
pLocalPlayer = null
--------------
-- fonts
font_Global_Arial = DrawManager:CreateFont("Arial", 15, false, false, false, false)
--------------
-- config/variable stuff
Box_visuals = 1
Box_name = 1
Aimbot_enabled = 1
--------------
--------------
function DrawBox(pEntity)
    local vEyePos = pEntity:GetEyePos()
    local vOrigin = pEntity:GetAbsOrigin()
    local vHeadScreen = Vector()
    local vOrigScreen = Vector()
    Utils:WorldToScreen(vEyePos, vHeadScreen)
    Utils:WorldToScreen(vOrigin, vOrigScreen)
    local iBoxHeight = math.abs(vHeadScreen.Y - vOrigScreen.Y)
    local iBoxWidth = iBoxHeight / 1.8
    if Box_name == 1 then
        DrawManager:Text(font_Global_Arial, vHeadScreen.X - 5, vHeadScreen.Y + 15, pEngine:GetClientName(pEntity:GetIndex()), 124, 252, 0, 255)
    end
    -- esp/box names
    DrawManager:DrawRect(vHeadScreen.X - iBoxWidth / 2, vHeadScreen.Y, iBoxWidth, iBoxHeight, 255, 0, 255, 255)
end
--------------
function DrawEnabled()
    if Box_visuals == 1 then
        DrawManager:Text(font_Global_Arial, 700, 0, "Box on", 124, 252, 0, 255)
    end
    if Box_name == 1 then
        DrawManager:Text(font_Global_Arial, 600, 0, "Box names", 124, 252, 0, 255)
    end
    if Aimbot_enabled == 1 then
        DrawManager:Text(font_Global_Arial, 500, 0, "Aimbot", 124, 252, 0, 255)
    end
end
--------------
function SanityChecks() -- just normal sanity checks for easy checking, no need to waste lines/time/whatever
    if not pEngine:IsInGame() then return false end
    if not pEngine:IsConnected() then return false end
    if pLocalPlayer == null then return false end
    if not pLocalPlayer:IsValid() then return false end
    if not pLocalPlayer:IsAlive() then return false end
    return true
end
--------------
function Aimbot(bCmd)
    if Aimbot_enabled == 1 then
        if not SanityChecks() then return end
        for i = 1, pEntityList:GetHighestEntityIndex() do
            local pEntity = pEntityList:GetEntityFromIndex(i)
            if pEntity:IsValid() then
                if pEntity:GetClassId() == 38 then
                    if pEntity:IsAlive() and i ~= pEngine:GetLocalPlayer() then
                        if pEntity:GetTeam() ~= pLocalPlayer:GetTeam() then
                            local Aim_pos = pEntity:GetEyePos() -- maybe change to closest hitbox later
                            local Aim_ang = Utils:CalcAngle(Aim_pos, pLocalPlayer:GetEyePos())
                            bCmd:SetViewAngles(Aim_ang)
                            DrawManager:Text(font_Global_Arial, 400, 40, "Aiming", 124, 252, 0, 255)
                        end
                    end
                end
            end
        end
    end
end
--------------
function OnCreateMove(pCmd)
    pLocalPlayer = pEntityList:GetEntityFromIndex(pEngine:GetLocalPlayer()) --sets local player variable
    Aimbot(pCmd)
end
--------------
function OnPaint(panel)
    if not SanityChecks() then return end
    DrawEnabled() -- draws enabled things
    if Box_visuals == 1 then
        for i = 1, pEntityList:GetHighestEntityIndex() do
            local pEntity = pEntityList:GetEntityFromIndex(i)
            if pEntity:IsValid() then
                if pEntity:GetClassId() == 38 then
                    if pEntity:IsAlive()
                        and not pEntity:IsDormant()
                        and i ~= pEngine:GetLocalPlayer() then
                        DrawBox(pEntity)
                    end
                end
            end
        end
    end
end
--------------
--hooks
Hooks:Register(HOOK_PAINTTRAVERSE, OnPaint) --onpaint aka painttraverse thing
Hooks:Register(HOOK_CREATEMOVE, OnCreateMove) --createmove thing
--------------