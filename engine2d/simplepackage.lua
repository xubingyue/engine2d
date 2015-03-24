-- It's a simple sprite package warpper, use your own asset format instead.

local engine2d = require "engine2d"
local ppm = require "engine2d.ppm"
local pack = require "engine2d.spritepack"
local sprite = require "engine2d.sprite"

-- This limit defined in texture.c
local MAX_TEXTURE = 128

local textures = {}
local packages = {}

local spack = {}
local package_pattern

local function require_tex(filename)
	print("require_tex----called=>",filename)
	local tex = #textures
	assert(tex < MAX_TEXTURE)
	table.insert(textures, filename)
	print("load ppm.texture func  ==>",tex)
	ppm.texture(tex,filename)
	return tex
end

function spack.path(pattern)
	package_pattern = pattern
end

local function realname(filename)
	print("realname==>",filename,package_pattern)
	assert(package_pattern, "Need a pattern")
	return string.gsub(package_pattern,"([^?]*)?([^?]*)","%1"..filename.."%2")
end

function spack.preload(packname)
	print("spack.preload...called=>",packname)
	if packages[packname] then
		return packages[packname]
	end
	local p = {}
	local filename = realname(packname)
	--print("filename==>",filename)
	p.meta = assert(pack.pack(dofile(filename .. ".lua")))

	p.tex = {}
	for i=1,p.meta.texture do
		p.tex[i] = require_tex(filename .. "." .. i)
	end
	pack.init(packname, p.tex, p.meta)
	packages[packname] = p
end

function spack.preload_raw(packname)
	if packages[packname] then
		return packages[packname]
	end
	local p = {}
	local filename = realname(packname)
	local data = io.open(filename..".raw", "rb"):read("*a")
	p.meta = assert(pack.import(data))

	p.tex = {}
	for i=1,p.meta.texture do
		p.tex[i] = require_tex(filename .. "." .. i)
	end
	pack.init(packname, p.tex, p.meta)
	packages[packname] = p
end

function engine2d.sprite(packname, name)
	if packages[packname] == nil then
		spack.preload(packname)
	end
	return sprite.new(packname, name)
end

function engine2d.load_texture(filename)
	return require_tex(filename)
end

function spack.load(tbl)
	print("spack.load.....called",tbl.pattern)
	spack.path(assert(tbl.pattern))
	for _,v in ipairs(tbl) do
		spack.preload(v)
		collectgarbage "collect"
	end
end

function spack.load_raw(tbl)
	spack.path(assert(tbl.pattern))
	for _,v in ipairs(tbl) do
		spack.preload_raw(v)
	end
	collectgarbage "collect"
end

function spack.texture(packname, index)
	if packages[packname] == nil then
		spack.preload(packname)
	end
	return packages[packname].tex[index or 1]
end

function spack.export(outdir, tbl)
	spack.path(assert(tbl.pattern))
	for _, packname in ipairs(tbl) do
		print("packname    ", packname, outdir, tbl.pattern)
		local filename = string.gsub(outdir..tbl.pattern,
				"([^?]*)?([^?]*)", "%1"..packname.."%2")
		print("spack.export     ",  filename.. ".raw")

		local meta = assert(pack.pack(dofile(filename .. ".lua")))
		local output = pack.export(meta)

		local file = io.open(filename .. ".raw", "w+")
		file:write(output)
		file:close()
	end
end

return spack
