local sprite = require "engine2d.sprite"
local fw 	 = require "engine2d.framework"

local engine2dx = {}


engine2dx.texture = require("engine2dx.texture")
engine2dx.texture.init()

engine2dx.package = require("engine2dx.package")
function  engine2dx.sprite( package,name )
	engine2dx.package:prepare_package(package)
	return sprite.new(package,name)
end

engine2dx.render = require("engine2dx.render")
engine2dx.render:init(fw.GameInfo.width,fw.GameInfo.height)

engine2dx.animation = require("engine2dx.animation")
engine2dx.animation:init(fw.GameInfo.logic_frame)

engine2dx.game_stat = require("engine2dx.game_stat")

return engine2dx