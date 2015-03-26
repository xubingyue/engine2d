


local shader = require "engine2d.shader"

local M ={}

M.blend_cfg = {
	add = {1,1},
	add_masked = {1,1},
 	test = {0x0301,0x0305}
}

function M.begin_blend(mode)
	if not mode or mode == "normal" then return true end
	local cfg = rawget(M.blend_cfg, mode)
	if not cfg then return end
	shader.blend(cfg[1], cfg[2])
	return true
end

function  M.end_blend()
	shader.blend()
end
return M