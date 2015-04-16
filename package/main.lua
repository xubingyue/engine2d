local ej = require "engine2d"
local fw = require "engine2d.framework"
local pack = require "engine2d.simplepackage"

local shader = require "dawn_shader"

local scene = require "dawn_scene"



local function init()
	math.randomseed(os.time())

	pack.load {
		pattern = fw.WorkDir..[[package/asset/?]],
	    "dawn",
	}
	shader:init()
	scene:init()
end

init()

-- game callback
local game = {}

function game.update()
	scene:update()
end

function game.drawframe()
	ej.clear(0xff000000)
	scene:draw()
end

local last_x
function game.touch(what, x, y)
	if what == "BEGIN" then
		scene:pause_time(true)
	elseif what == "END" then
		scene:pause_time(false)
	elseif what == "MOVE" then
		scene:shift_time(x - last_x)
	end

	last_x = x
end

function game.message(id, state, data, n)
	if data == "LEFT" or data == "RIGHT" then
		scene:layout_sim(true)
	else
		scene:layout_sim(false)
	end
end

function game.handle_error(...)
end

function game.on_resume()
end

function game.on_pause()
end

ej.start(game)
