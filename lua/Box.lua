local Box = Object:extend()

function Box:new(type, x, y, opts)
  self.type = type
  self.x, self.y = x, y
  local opts = opts or {}
  for k, v in pairs(opts) do
    self[k] = v
  end
  self.radius = 18
  self.img = love.graphics.newImage("box.jpg")
  self.dead = false
end


function Box:update(dt)
  local switch = {
    [0] = function()
      end,
    [1] = function()
        self.x = self.x - self.speed *dt 
      end,
    [2] = function()
        self.y = self.y - self.speed *dt 
      end,
    [3] = function()
        self.y = self.y + self.speed *dt 
      end,   
    [4] = function()
        self.x = self.x + self.speed *dt 
      end,
    }
  switch[self.status]()
  -- change images with the step
end

function Box:draw()
  love.graphics.setColor(217, 141, 74)
  --love.graphics.rectangle('fill', self.x-self.radius*0.9, self.y-self.radius*0.9, self.radius*2*0.9, self.radius*2*0.9)
  love.graphics.draw(self.img, self.x - self.radius*0.9, self.y - self.radius*0.9)
end

function Box:canBePushed(direction)
  local vertex1x, vertex1y, vertex2x, vertex2y = getTwoVertex[direction](self.x, self.y, self.radius)
  local obj1type, obj1 = checkPosition(vertex1x, vertex1y)
  local obj2type, obj2 = checkPosition(vertex2x, vertex2y)
  if(obj1type == 'Space' and obj2type == 'Space') then 
    return true
  else
    return false
  end
  
end


return Box