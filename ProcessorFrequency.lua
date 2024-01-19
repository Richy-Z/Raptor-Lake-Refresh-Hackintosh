--[[
    NSC Information
    Revision 1
    Author iirzd
    Numelon Softworks

    Created Friday 29th December 2023 at 15:49
    Updated Saturday 30th December 2023 at 00:09
]]
--[[
    Latest update:
    - Written script
]]
-- This script is used to determine the LFM value of the processor to use with CPUFriend.

-- USER CONFIGURATION
local intervalMs = 1000


-- Actual script
if require("uv").getuid() ~= 0 then print("This script requires elevated privileges! Please run it with sudo.") return end

while true do
    local command = "powermetrics --samplers cpu_power -i ".. intervalMs
    local handle = io.popen(command)

    local processorInfoBuffer = {}

    -- Read the output line by line
    for line in handle:lines() do
        -- Retrieve CPU Core Number and frequency
        if string.match(line, "duty cycles") then
            table.insert(processorInfoBuffer, tostring(tonumber(line:sub(5, 6)) + 1))
        elseif string.match(line, "CPU Average frequency as fraction of nominal") then
            local pattern = "CPU Average frequency as fraction of nominal: (%d+%.?%d*)%% %((%d+%.?%d*) Mhz%)"
            local percentage, frequency = line:match(pattern)

            if not frequency then goto errored end

            table.insert(processorInfoBuffer, tonumber(frequency))
        end

        if #processorInfoBuffer >= 32 * 2 then
            local fullInformation = {}
            for i=1, #processorInfoBuffer, 2 do
                local coreNumber = processorInfoBuffer[i]
                local frequency = processorInfoBuffer[i + 1]
    
                if type(coreNumber) == "string" and type(frequency) == "number" then
                    fullInformation[tonumber(coreNumber)] = {
                        coreNumber = coreNumber,
                        frequency = frequency
                    }
                else
                    print("Warning: Input mismatch for core ".. i)
                end
            end
    
            local lowest = math.huge
            local average = 0
            local highest = 0
            for i,v in pairs(fullInformation) do
                average = average + v.frequency
                if v.frequency < lowest then
                    lowest = math.floor(v.frequency)
                end
                if v.frequency > highest then
                    highest = math.floor(v.frequency)
                end
            end
            average = math.floor(average / #fullInformation)

            processorInfoBuffer = {}
            
            p(os.date("%H:%M:%S"), lowest, average, math.floor((lowest + highest) / 2), highest)
        end
    end
    ::errored::
end