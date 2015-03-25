print("engine2d/init.lua loading.....")
local shader = require "engine2d.shader"
print("engine2d/init.lua  engine2d.shader   loading.....")
local fw = require "engine2d.framework"

function fw.ENGINE2D_INIT()
--	shader.init()
end

shader.init()

local engine2d = {}

local touch = {
	"BEGIN",
	"END",
	"MOVE",
	"CANCEL"
}

local gesture = {
	"PAN",
	"TAP",
	"PINCH",
    "PRESS",
    "DOUBLE_TAP",
}

function engine2d.start(callback)
	print("engine2d.start--->loading")
     for k,v in ipairs(callback) do
     	print("k===>",k,"v====>",v)
     end

	fw.ENGINE2D_UPDATE = assert(callback.update)
	fw.ENGINE2D_DRAWFRAME = assert(callback.drawframe)

	fw.ENGINE2D_TOUCH = function(x,y,what,id)
		return callback.touch(touch[what],x,y,id)
	end
    fw.ENGINE2D_GESTURE = function(what, x1, y1, x2, y2, state)
		return callback.gesture(gesture[what], x1, y1, x2, y2, state)
	end
	fw.ENGINE2D_MESSAGE = assert(callback.message)
  	fw.ENGINE2D_HANDLE_ERROR = assert(callback.handle_error)
  	fw.ENGINE2D_RESUME = assert(callback.on_resume)
		fw.ENGINE2D_PAUSE = assert(callback.on_pause)
	fw.inject()
end

function engine2d.clear(color)
	--print("engine2d.clear---->loading",color)
	return shader.clear(color)
end

function engine2d.define_shader(args)
	return shader.define(args)
end

return engine2d
