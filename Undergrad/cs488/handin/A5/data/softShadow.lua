--a cornel box

red = gr.phongMat({1, 0, 0}, {1, 0, 0}, 2, 0, 0)
green = gr.phongMat({0, 1, 0}, {0, 1, 0}, 2, 0, 0)
blue = gr.phongMat({0, 0, 1}, {0, 0, 1}, 2, 0, 0)
white = gr.phongMat({1, 1, 1}, {1, 1, 1}, 25, 0, 0)
orange = gr.phongMat({1, 0.52, 0}, {1, 0.52, 0}, 2, 0, 0)
grey = gr.phongMat({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, 0, 0, 0)

glass1 = gr.transMat({0, 0, 1.0}, 1.333, 0.8, 1)
glass2 = gr.transMat({0, 0, 1.0}, 1.333, 0.8, 2)
glass3 = gr.transMat({0, 0, 1.0}, 1.333, 0.8, 3)

mat1 = gr.phongMat({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)
mat2 = gr.phongMat({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)
mat3 = gr.phongMat({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0, 0)

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



cyl1 = gr.cyllinder('')
cyl1:translate(1,-5,3.5)
cyl1:scale(0.1,10,0.1)
cyl1:set_material(red)
scene_root:add_child(cyl1)

cyl2 = gr.cyllinder('')
cyl2:translate(-3,-5,4)
cyl2:set_material(green)
scene_root:add_child(cyl2)

cone1 = gr.cone('')
cone1:translate(3,-5,4)
cone1:scale(0.5,1,0.5)
cone1:set_material(blue)
scene_root:add_child(cone1)

cube1 = gr.cube('')
cube1:rotate('y',40)
cube1:translate(-4.2,-5,6)
cube1:set_material(orange)
scene_root:add_child(cube1)

sphere1 = gr.sphere('')
sphere1:translate(-0.2, 4, 5)
sphere1:scale(0.2, 0.2, 0.2)
sphere1:set_material(grey)
scene_root:add_child(sphere1)





white_light = gr.light({0, 4.89, 5}, {0.9, 0.9, 0.9}, {1, 0, 0}, {6,1}, {0,1,0},{-1,0,0})



gr.render(scene_root, 'SS.png', 500, 500,
	  {0, 0, 20}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}, 1, 8, 0, {1, 15, 0})
