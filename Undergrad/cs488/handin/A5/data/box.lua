--a cornel box

require('readobj')
cow_poly = gr.mesh('cow', readobj('cow.obj'))


red = gr.phongMat({1, 0, 0}, {1, 0, 0}, 2, 0, 0)
green = gr.phongMat({0, 1, 0}, {0, 1, 0}, 2, 0, 0)
blue = gr.phongMat({0, 0, 1}, {0, 0, 1}, 2, 0, 0)
white = gr.phongMat({1, 1, 1}, {1, 1, 1}, 25, 0, 0)
orange = gr.phongMat({1, 0.52, 0}, {1, 0.52, 0}, 2, 0, 0)
grey = gr.phongMat({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, 0, 0, 0)

glass = gr.transMat({0.0, 0.0, 1.0}, 1.52, 0.95, 0)

mat3 = gr.phongMat({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.2, 20)

scene_root = gr.node('root')

box = gr.node('box')

left = gr.cube('left')
box:add_child(left)
left:set_material(red)
left:translate(-5, -5, 0)
left:scale(0.01, 10 , 10)

right = gr.cube('right')
box:add_child(right)
right:set_material(green)
right:translate(5, -5, 0)
right:scale(0.01, 10,10)


top = gr.cube('top')
box:add_child(top)
top:set_material(grey)
top:translate(-5, 4.9, 0)
top:scale(10, 0.01,10)

bottom = gr.cube('bottom')
box:add_child(bottom)
bottom:set_material(white)
bottom:translate(-5, -5, 0)
bottom:scale(10, 0.01,10)

back = gr.cube('back')
box:add_child(back)
back:set_material(white)
back:translate(-5, -5, 0)
back:scale(10, 10, 0.01)

scene_root:add_child(box)


sphere = gr.nh_sphere('',{0,-2,5},2)
sphere:set_material(glass)
scene_root:add_child(sphere)


white_light = gr.light({0, 4.89, 5}, {0.9, 0.9, 0.9}, {1, 0, 0}, {6,1}, {0,1,0},{-1,0,0})


gr.render(scene_root, 'box.png', 500, 500,
	  {0, 0, 20}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}, 1, 0, 0, {0.1, 10, 0})
