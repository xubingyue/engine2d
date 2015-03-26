local osutls = require "engine2dx.osutls.c"

local M = {}

M.exists = osutls.exists

M.read_file = osutls.read_file
M.delete_file = osutls.delete_file
M.write_file = osutls.write_file

return M