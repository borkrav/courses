--http://www.turbosquid.com/3d-models/free-3ds-mode-car-fictional/640082
--car from here

require('readobj')
car_poly = gr.mesh('cor', readobj('muscle.obj'))

red = gr.phongMat({1, 0, 0}, {1, 0, 0}, 25, 0.2, 0)
green = gr.phongMat({0, 1, 0}, {0, 1, 0}, 2, 0, 0)
blue = gr.phongMat({0, 0, 1}, {0, 0, 1}, 2, 0, 0)
white = gr.phongMat({1, 1, 1}, {1, 1, 1}, 1, 0, 0)
orange = gr.phongMat({1, 0.52, 0}, {1, 0.52, 0}, 2, 0, 0)
grey = gr.phongMat({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, 0, 0, 0)
black = gr.phongMat({0, 0, 0}, {0, 0, 0}, 1, 0, 0)

water = gr.transMat({0.0, 0.0, 1.0}, 1.333, 0.5, 1)

scene_root = gr.node('root')



scene_root = gr.node('root')

box = gr.node('box')

left = gr.cube('left')
box:add_child(left)
left:set_material(white)
left:translate(-7.5, -5, -5)
left:scale(0.01, 7 , 40)

right = gr.cube('right')
box:add_child(right)
right:set_material(white)
right:translate(7.5, -5, -5)
right:scale(0.01, 7 , 40)


top = gr.cube('top')
box:add_child(top)
top:set_material(white)
top:translate(-7.5, 2, -5)
top:scale(15, 0.01,40)

bottom = gr.cube('bottom')
box:add_child(bottom)
bottom:set_material(white)
bottom:translate(-7.5, -5, -5)
bottom:scale(15, 0.01,40)

waterlayer = gr.cube('water')
box:add_child(waterlayer)
waterlayer:set_material(water)
waterlayer:translate(-7.5, -4.9, -5)
waterlayer:scale(15, 0.1,40)

back = gr.cube('back')
box:add_child(back)
back:set_material(grey)
back:translate(-7.5, -5, -5)
back:scale(15, 7, 0.01)

front = gr.cube('front')
box:add_child(front)
front:set_material(white)
front:translate(-7.5, -5, 35)
front:scale(15, 7, 0.01)

scene_root:add_child(box)


car_poly:set_material(red)
car_poly:scale(0.03,0.03,0.03)
car_poly:translate(0,-130,200)
car_poly:rotate('y', -135)
scene_root:add_child(car_poly)

pedistal = gr.cube('')
pedistal:translate(1,-5.1,10)
pedistal:rotate('y', 135)
pedistal:scale(8,0.5,5)
pedistal:set_material(white)
scene_root:add_child(pedistal)

cyl = gr.cyllinder('')
cyl:translate(-4.2,-4.6,4.5)
cyl:scale(0.1,0.5,0.1)
cyl:set_material(black)
scene_root:add_child(cyl)

cyl2 = gr.cyllinder('')
cyl2:translate(4,-4.6,6.5)
cyl2:scale(0.1,0.5,0.1)
cyl2:set_material(black)
scene_root:add_child(cyl2)

cyl3 = gr.cyllinder('')
cyl3:translate(1,-4.6,9.6)
cyl3:scale(0.1,0.5,0.1)
cyl3:set_material(black)
scene_root:add_child(cyl3)


white_light = gr.light({0, 1, -4.98}, {0.9, 0.9, 0.9}, {1, 0, 0}, {10,1}, {0,0,1},{-1,0,0})


gr.render(scene_root, 'finalScene.png', 500, 500,
	  {0, -2, 20}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}, 0, 1, 1, {0.3, 10, 4})
