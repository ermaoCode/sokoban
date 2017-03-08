Object = require "lib/classic"
Timer = require "lib/hump/timer"
Player = require "Player"
Box = require "Box"
Wall = require "Wall"

map = 
{
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1,  0,  0,  0,  0,  0, -1, -1},
	{-1, -1,  0,  2,  0, -1, -1, -1, -1},
	{-1, -1, -1, -2,  0,  0,  0,  0, -1},
	{-1,  0,  0,  0, -1, -2, -1,  0, -1},
	{-1,  0, -2,  0, -1,  0,  0,  0, -1},
	{-1,  0,  0,  0, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1}
}
targetArray = 
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
}

getTwoVertex = {
  [1] = function(x, y, radius)
      return  x-radius-2, y+radius, x-radius-2, y-radius
    end,
  [2] = function(x, y, radius)
      return  x+radius, y-radius-2, x-radius, y-radius-2
    end,
  [3] = function(x, y, radius)
      return  x+radius, y+radius+2 ,x-radius, y+radius+2
    end,   
  [4] = function(x, y, radius)
      return  x+radius+2, y+radius, x+radius+2, y-radius
    end
  }

function love.load()
  if arg[#arg] == "-debug" then require "mobdebug".start() end
  timer = Timer()
  
  game_objects = {}
  --player = createGameObject('Player', 100, 100)
  local typeArr = {[-1] = 'Wall', [-2] = 'Box', [2] = 'Player'}
  for i = 1, #map do
    for j = 1, #map[i] do
      if (map[i][j] < 0) then
        createGameObject(typeArr[map[i][j]], 40*j, 40*i)
      elseif (map[i][j] == 2) then
        player = createGameObject('Player', 40*j, 40*i)
      end
    end
  end
  targetImg = love.graphics.newImage("target.png")
  
end

function love.update(dt)
  if (player.direction == 0) then 
    player:stop()
  else
    local vertex1x, vertex1y, vertex2x, vertex2y = getTwoVertex[player.direction](player.x, player.y, player.radius)
    local obj1type, obj1 = checkPosition(vertex1x, vertex1y)
    local obj2type, obj2 = checkPosition(vertex2x, vertex2y)
    
    if(obj1type == 'Space' and obj2type == 'Space') then 
      player:walk(dt)
    elseif (obj1type == 'Box' and obj2type == 'Box' and obj1 == obj2) then
      player:push(obj1, dt)
    else
      player:cannotPush(dt)
    end
    
  end
  --player:update(dt)
end

function love.draw()
  for i = 1, #targetArray do
    for j = 1, #targetArray[i] do
      if (targetArray[i][j] == 1) then
        love.graphics.draw(targetImg, 40*j - 20, 40*i - 20)
      end
    end
  end
  for _, game_object in ipairs(game_objects) do
    game_object:draw()
  end
end

function love.keypressed(key)
  if key == 'a' then
    player.direction = 1
  elseif key == 'w' then
    player.direction = 2
  elseif key == 's' then
    player.direction = 3
  elseif key == 'd' then
    --print('key pressed!')
    player.direction = 4
  end
  
end

function love.keyreleased(key)
  player.direction = 0
end


function createGameObject(type, x, y, opts)
  local game_object = _G[type](type, x, y, opts)
  table.insert(game_objects, game_object)
  return game_object
end

function checkPosition(x, y)
  for _, game_object in ipairs(game_objects) do
    if (abs(game_object.x - x) - 1 <= game_object.radius and abs(game_object.y - y) - 1 <= game_object.radius ) then
      return game_object.type, game_object
    end
  end
  
  return 'Space', nil
end

function abs(x)
  if (x >= 0) then
    return x
  else
    return -1 * x
  end
end

  
