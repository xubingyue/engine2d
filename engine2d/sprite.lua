
print("sprite....load")
local debug = debug
local c = require "engine2d.sprite.c"
local pack = require "engine2d.spritepack"
local shader = require "engine2d.shader"
local richtext = require "engine2d.richtext"



local setmetatable = setmetatable
local method = c.method
local method_fetch = method.fetch
local method_test = method.test
local method_fetch_by_index = method.fetch_by_index
local dfont_method = c.dfont_method
local fetch
local test

local get = c.get
local set = c.set

local get_material = get.material
function get:material()
	print("get:material  ... called==>")
	local m = get_material(self)
	if m == nil then
		local prog
		m, prog = c.new_material(self)
		if m == nil then
			return
		end
		local meta = shader.material_meta(prog)
		setmetatable(m, meta)
	end

	return m
end

local set_program = set.program
function set:program(prog)
	print("set:program ... called===>",prog)
	if prog == nil then
		set_program(self)
	else
		set_program(self, shader.id(prog))
	end
end

local set_text = set.text
function set:text(txt)
	print("set:text...called===>",txt)
	if not txt or txt == "" then
		set_text(self, nil)
	else
		local t = type(txt)
		assert(t=="string" or t=="number")
		set_text(self, richtext:format(self, tostring(txt)))
	end
end

local sprite_meta = {}

function sprite_meta.__index(spr, key)
	--print("sprite_meta.__index  called====>",spr,key)
	if method[key] then
		return method[key]
	end
	local getter = get[key]
	if getter then
		return getter(spr)
	end
	local child = fetch(spr, key)

	if child then
		return child
	else
		print("Unsupport get " ..  key)
		return nil
	end
end

function sprite_meta.__newindex(spr, key, v)
	--print("sprite_meta.__newindex  called===>",spr,key,v)
	local setter = set[key]
	if setter then
		setter(spr, v)
		return
	end
	assert(debug.getmetatable(v) == sprite_meta, "Need a sprite")
	method.mount(spr, key, v)
end

local get_parent = get.parent
function get:parent()
	print("get_parent  called==>")
	local p = get_parent(self)
	if p and not getmetatable(p) then
		return debug.setmetatable(p, sprite_meta)
	end
	return p
end

-- local function
function fetch(spr, child)
	print("fetch  called==>",spr,child)
	local cobj = method_fetch(spr, child)
	if cobj then
		return debug.setmetatable(cobj, sprite_meta)
	end
end

-- local function
function test(...)
	print("sprite.lua  test====>",...)
	local cobj = method_test(...)
	if cobj then
		return debug.setmetatable(cobj, sprite_meta)
	end
end

local function fetch_by_index(spr, index)
	print("fetch_by_index....called===>",spr,index)
	local cobj = method_fetch_by_index(spr, index)
	if cobj then
		return debug.setmetatable(cobj, sprite_meta)
	end
end

method.fetch = fetch
method.fetch_by_index = fetch_by_index
method.test = test

local sprite = {}

function sprite.new(packname, name)
	--print("sprite.new---> called=====",packname,"    ",name)
	local pack, id = pack.query(packname, name)
	local cobj = c.new(pack,id)
	if cobj then
		return debug.setmetatable(cobj, sprite_meta)
	end
end

function sprite.label(tbl)
	print("sprite.label---> called.....")
	local size = tbl.size or tbl.height - 2
	local l = (c.label(tbl.width, tbl.height, size, tbl.color, tbl.align))
	if l then
		l = debug.setmetatable(l, sprite_meta)
		if tbl.text then
			l.text = tbl.text
		end
		return l
	end
end

function sprite.proxy()
	print("sprite.proxy---> called.....")
	local cobj = c.proxy()
	return debug.setmetatable(cobj, sprite_meta)
end

local dfont_meta = {}

function dfont_meta.__index(spr, key)
	--print("dfont_meta.__index---> called.....")
	if dfont_method[key] then
		return dfont_method[key]
	else
		error("Unsupport dfont get " ..  key)
	end
end

function sprite.dfont(width, height, fmt, tid)
	print("sprite.dfont---> called.....")
	local cobj = c.dfont(width, height, fmt, tid)
	return debug.setmetatable(cobj, dfont_meta)
end

return sprite
