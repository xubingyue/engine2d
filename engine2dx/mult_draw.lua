
local matrix = require "engine2d.matrix"

local M = {}

function M:init()
	self.matrix_cache = {}
	self.active_matrix = {}
	self.active_colors = {}
end

function M:draw_points(srt, spr, points, pcnt, color)
	if not points then return end
	if pcnt <= 0 then return end
	assert(pcnt*2<=#points)

	color = color or 0xFFFFFFFF

	local mcnt = #self.matrix_cache
	local delta = pcnt - mcnt
	while delta > 0 do
		table.insert(self.matrix_cache, matrix())
		delta = delta-1
	end

	local x, y, mat
	for i=1, pcnt do
		x, y = points[2*i-1], points[2*i]
		mat = self.matrix_cache[i]
		mat:identity()
		mat:trans(x, y)
		self.active_matrix[i] = mat
		self.active_colors[i] = color
	end

	spr:multi_draw(srt, pcnt, self.active_matrix, self.active_colors)
end

M:init()
return M
