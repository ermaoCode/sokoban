local Wall = Object:extend()

function Wall:new(type, x, y, opts)
  self.type = type
  self.x, self.y = x, y
  local opts = opts or {}
  for k, v in pairs(opts) do
    self[k] = v
  end
  self.radius = 20
  self.img = love.graphics.newImage("wall.jpg")
  self.dead = false
end


function Wall:draw()
  love.graphics.setColor(114, 159, 194)
  --love.graphics.rectangle('fill', self.x-self.radius, self.y-self.radius, self.radius*2, self.radius*2)
  love.graphics.draw(self.img, self.x - self.radius, self.y - self.radius)
end

return Wall