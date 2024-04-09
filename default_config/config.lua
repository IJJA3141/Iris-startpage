---@class Array<T>: { [integer]: T }

---@class Button
---@field image string
---@field label string
---@field command function

---@class Row
---@field title string
---@field buttons Array<Button>

---@class Page
---@field name string
---@field image string
---@field top_button Row
---@field center_button Row
---@field bottom_button Row

---@class Config
---@field image_width integer
---@field width integer
---@field height integer
---@field use_local boolean
---@field is_overlay boolean
---@field pages Array<Page>

---@type Config
local default_config = {
	image_width = 200,
	width = 1500,
	height = 400,
	use_local = true,
	is_overlay = true,

	pages = {
		{
			name = "exemple config",
			image = "~/.config/iris/test.jpg",
			top_button = {
				title = "a row",
				buttons = {
					{
						label = "exemple button",
						image = "/etc/iris/logo.png",
						command = function()
							os.execute("notify-send -a iris 'This is an exemple command'")
						end,
					},
				},
			},
			center_button = {},
			bottom_button = {},
		},
	},
}

package.path = package.path
	.. ";"
	.. os.getenv("HOME")
	.. ".config/iris/?.lua"
	.. ";"
	.. os.getenv("XDG_CONFIG_HOME")
	.. "/iris/?.lua"

local f = io.open(os.getenv("HOME") .. "/.config/iris/init.lua", "r")
if f ~= nil then
	io.close(f)
	local user_config = require("init")
	for k, v in pairs(user_config) do
		if default_config[k] ~= nil then
			default_config[k] = v
		end
	end
end

Config = default_config
