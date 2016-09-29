--a cornel box

red = gr.phongMat({1, 0, 0}, {1, 0, 0}, 2, 0, 0)
green = gr.phongMat({0, 1, 0}, {0, 1, 0}, 2, 0, 0)
blue = gr.phongMat({0, 0, 1}, {0, 0, 1}, 2, 0, 0)
white = gr.phongMat({1, 1, 1}, {1, 1, 1}, 25, 0, 0)
orange = gr.phongMat({1, 0.52, 0}, {1, 0.52, 0}, 2, 0, 0)
grey = gr.phongMat({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, 0, 0, 0)

glass = gr.transMat({0.0, 0.0, 1.0}, 1.52, 0.95, 0)

mat3 = gr.phongMat({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.2, 10)

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
bottom:set_material(grey)
bottom:translate(-5, -5, 0)
bottom:scale(10, 0.01,10)

back = gr.cube('back')
box:add_child(back)
back:set_material(white)
back:translate(-5, -5, 0)
back:scale(10, 10, 0.01)

scene_root:add_child(box)

sphere = gr.nh_sphere('',{0,-4,5},1.4)
sphere:set_material(blue)
cube = gr.nh_box('',{-1,-5,4},2)
cube:set_material(red)
scene_root:add_child(cube)
cube:csg(sphere, 'd')
cube:rotate('y', 40)

sphere2 = gr.nh_sphere('',{0,-4,5},1.4)
sphere2:set_material(blue)
cube2 = gr.nh_box('',{-1,-5,4},2)
cube2:set_material(red)
scene_root:add_child(cube2)
cube2:csg(sphere2, 'u')

sphere3 = gr.nh_sphere('',{0,-4,5},1.4)
sphere3:set_material(blue)
cube3 = gr.nh_box('',{-1,-5,4},2)
cube3:set_material(red)
scene_root:add_child(cube3)
cube3:csg(sphere3, 'n')
cube3:rotate('y', -40)


sphere4 = gr.nh_sphere('',{-0.5,0,2},1)
sphere4:set_material(blue)
sphere5 = gr.nh_sphere('',{0.5,0,2},1)
sphere5:set_material(red)
scene_root:add_child(sphere5)
sphere5:csg(sphere4, 'u')

sphere6 = gr.nh_sphere('',{2.1,0,2},1)
sphere6:set_material(blue)
sphere7 = gr.nh_sphere('',{3.1,0,2},1)
sphere7:set_material(red)
scene_root:add_child(sphere7)
sphere7:csg(sphere6, 'n')

sphere8 = gr.nh_sphere('',{-3,0,2},1)
sphere8:set_material(blue)
sphere9 = gr.nh_sphere('',{-4,0,2},1)
sphere9:set_material(red)
scene_root:add_child(sphere9)
sphere9:csg(sphere8, 'd')
sphere9:rotate('y',-30)
sphere9:translate(2.5,0,1)





white_light = gr.light({0, 4.89, 5}, {0.9, 0.9, 0.9}, {1, 0, 0}, {6,1}, {0,1,0},{-1,0,0})



gr.render(scene_root, 'csg.png', 500, 500,
	  {0, 0, 20}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}, 1, 4, 0, {1, 15, 0})
