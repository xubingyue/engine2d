return {

{
	type = "label",
	id = 8,
	export = "default_label",
	width = 200,
	height = 100,
	font = "",
	align = 0,
	size = 16,
	color = 0xffffffff,
	noedge = true,
},
{
	type = "picture",
	id = 5,
	export = "idle",
	{
		tex = 1,
		src = { 226, 1, 226, 101, 335, 101, 335, 1 },
		screen = { -864, -800, -864, 800, 880, 800, 880, -800 },
	},
},
{
	type = "picture",
	id = 2,
	export = "die3",
	{
		tex = 1,
		src = { 1, 109, 1, 212, 106, 212, 106, 109 },
		screen = { -656, -848, -656, 800, 1024, 800, 1024, -848 },
	},
},
{
	type = "picture",
	id = 3,
	export = "die4",
	{
		tex = 1,
		src = { 1, 214, 1, 322, 103, 322, 103, 214 },
		screen = { -592, -864, -592, 864, 1040, 864, 1040, -864 },
	},
},
{
	type = "picture",
	id = 4,
	export = "die5",
	{
		tex = 1,
		src = { 1, 324, 1, 430, 103, 430, 103, 324 },
		screen = { -592, -832, -592, 864, 1040, 864, 1040, -832 },
	},
},
{
	type = "picture",
	id = 0,
	export = "die1",
	{
		tex = 1,
		src = { 1, 1, 1, 107, 120, 107, 120, 1 },
		screen = { -1040, -832, -1040, 864, 864, 864, 864, -832 },
	},
},
{
	type = "picture",
	id = 6,
	export = "stone",
	{
		tex = 1,
		src = { 337, 1, 337, 99, 437, 99, 437, 1 },
		screen = { -800, -768, -800, 800, 800, 800, 800, -768 },
	},
},
{
	type = "picture",
	id = 1,
	export = "die2",
	{
		tex = 1,
		src = { 122, 1, 122, 111, 224, 111, 224, 1 },
		screen = { -592, -880, -592, 880, 1040, 880, 1040, -880 },
	},
},
{
	type = "animation",
	id = 7,
	export = "die",
	component = {
		{ id = 0 },
		{ id = 1 },
		{ id = 2 },
		{ id = 3 },
		{ id = 4 },
	},
	{
		{ 0 },
		{ 1 },
		{ 2 },
		{ 3 },
		{ 4 },
	},
},

}
