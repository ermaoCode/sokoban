local Player = Object:extend()

function Player:new(type, x, y, options)
  self.type = type
  self.x, self.y = x, y
  local opts = options or {}
  for k, v in pairs(opts) do
    self[k] = v
  end
  self.step = 0
  self.direction = 0
  self.speed = 100
  timer:every(0.2, function()
      self.step = (self.step + 1) % 8
    end
  )
  self.img = love.graphics.newImage("role.png")
  self.radius = 10
  self.dead = false
end


function Player:update(dt)
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
      end
    }
  switch[self.direction]()
  -- change images with the step
end

function Player:draw()
  love.graphics.setColor(255,255,255)
  --love.graphics.circle('fill', self.x, self.y ,10)
  love.graphics.draw(self.img, self.x - self.radius, self.y - self.radius)
end

function Player:walk(dt)
  self.speed = 100
  self:update(dt)
end

function Player:stop()
  
end

function Player:push(box, dt)
  if (box:canBePushed(self.direction)) then 
    self.speed = 50
    local switch = {
      [1] = function()
          self.x = self.x - self.speed *dt 
          box.x = box.x - self.speed *dt 
        end,
      [2] = function()
          self.y = self.y - self.speed *dt 
          box.y = box.y - self.speed *dt 
        end,
      [3] = function()
          self.y = self.y + self.speed *dt 
          box.y = box.y + self.speed *dt 
        end,   
      [4] = function()
          self.x = self.x + self.speed *dt 
          box.x = box.x + self.speed *dt 
        end
    }
    switch[self.direction]()  
  else
    self:cannotPush(dt)
  end
end

function Player:cannotPush(dt)
  self.speed = 0
  self:update(dt)
end


return Player