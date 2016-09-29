-- A simple scene with some miscellaneous geometry.

require('readobj')

cow_poly = gr.mesh('cow', readobj('cow.obj'))

hide = gr.material({0.84, 0.6, 0.53}, {0.3, 0.3, 0.3}, 20)
silver = gr.material({0.7, 0.7, 0.7}, {1, 1, 1}, 25)
orange = gr.material({1, 0.3, 0}, {0.5, 0.4, 0.8}, 25)
blue = gr.material({0.0, 0.0, 0.6}, {0.1, 0.1, 0.5}, 25)
lightOrange = gr.material({1.0, 0.6, 0.1}, {1.0, 0.6, 0.1}, 25)
white = gr.material({0.9, 0.9, 0.9}, {0.9, 0.9, 0.9}, 25)

scene_root = gr.node('root')



earth = gr.sphere('earth')
earth:translate(1000, 50, -400)
earth:scale(700,700,700)
scene_root:add_child(earth)
earth:set_material(blue)

moon = gr.sphere('moon')
moon:translate(-200, -200, 50)
moon:scale(100,100,100)
scene_root:add_child(moon)
moon:set_material(white)


-- A small stellated dodecahedron.

sun = gr.sphere('sun')
sun:translate(-510,400,-1000);
sun:scale(40, 40, 40);
scene_root:add_child(sun)
sun:set_material(lightOrange)



rocket = gr.node('rocket')

nose = gr.mesh('nose', {
{0,0,0}, {1,0,0}, {2,0,-1}, {2,0,-2},
{1,0,-3}, {0,0,-3}, {-1,0,-2}, {-1,0,-1},
{0.5, 1, -1.5} 
 

} , {
{0,1,8},
{1,2,8},
{2,3,8},
{3,4,8},
{4,5,8},
{5,6,8},
{6,7,8},
{7,1,8}

}
)


body = gr.mesh('body', {
{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
{-1,0,-1}, {-1,1,-1}, {-1,1,-2}, {-1,0,-2},
{2,0,-1}, {2,0,-2}, {2,1,-2}, {2,1,-1}, 
{0,0,-3}, {0,1,-3}, {1,1,-3}, {1,0,-3}
} , {
{0,1,2,3},
{4,5,6,7},
{8,9,10,11},
{12,13,14,15},

{0,3,5,4},
{1,8,11,2},
{7,6,13,12},
{15,14,10,9}

}
)

bodyl = gr.mesh('bodyl', {
{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
{-1,0,-1}, {-1,1,-1}, {-1,1,-2}, {-1,0,-2},
{2,0,-1}, {2,0,-2}, {2,1,-2}, {2,1,-1}, 
{0,0,-3}, {0,1,-3}, {1,1,-3}, {1,0,-3}
} , {
{0,1,2,3},
{4,5,6,7},
{8,9,10,11},
{12,13,14,15},

{0,3,5,4},
{1,8,11,2},
{7,6,13,12},
{15,14,10,9},
{3,2,11,10,14,15,6,5}

}
)

nose:set_material(silver)
nose:translate(0,1,0)
rocket:add_child(nose)
body:set_material(silver)

rocket:add_child(body)

bodyl:translate(0,-2,0)
rocket:add_child(bodyl)
bodyl:set_material(silver)

c1 = gr.sphere('c1')
c1:translate(0,-0.5,-0.1)
c1:scale(0.1,0.6,0.1)
c1:set_material(silver)
rocket:add_child(c1)

c2 = gr.sphere('c2')
c2:translate(1,-0.5,-0.1)
c2:scale(0.1,0.6,0.1)
c2:set_material(silver)
rocket:add_child(c2)

c3 = gr.sphere('c3')
c3:translate(1.9,-0.5,-1)
c3:scale(0.1,0.6,0.1)
c3:set_material(silver)
rocket:add_child(c3)

c4 = gr.sphere('c4')
c4:translate(1.9,-0.5,-2)
c4:scale(0.1,0.6,0.1)
c4:set_material(silver)
rocket:add_child(c4)

c5 = gr.sphere('c5')
c5:translate(0,-0.5,-3)
c5:scale(0.1,0.6,0.1)
c5:set_material(silver)
rocket:add_child(c5)

c6 = gr.sphere('c6')
c6:translate(1,-0.5,-3)
c6:scale(0.1,0.6,0.1)
c6:set_material(silver)
rocket:add_child(c6)

c7 = gr.sphere('c7')
c7:translate(-0.9,-0.5,-1)
c7:scale(0.1,0.6,0.1)
c7:set_material(silver)
rocket:add_child(c7)

c8 = gr.sphere('c8')
c8:translate(-0.9,-0.5,-2)
c8:scale(0.1,0.6,0.1)
c8:set_material(silver)
rocket:add_child(c8)



b1 = gr.cube('b1')
b1:translate(-0.5,-2.3,-2.5)
b1:scale(2,0.25,2)
b1:set_material(orange)
rocket:add_child(b1)

b2 = gr.cube('b2')
b2:translate(-0.25,-2.5,-2.5)
b2:scale(1.5,0.25,1.5)
b2:set_material(orange)
rocket:add_child(b2)

b3 = gr.cube('b3')
b3:translate(-0,-2.7,-2.5)
b3:scale(1,0.25,1)
b3:set_material(orange)
rocket:add_child(b3)

b4 = gr.cube('b4')
b4:translate(0.25,-2.9,-2.5)
b4:scale(0.5,0.25,0.5)
b4:set_material(orange)
rocket:add_child(b4)

cow = gr.sphere('cow')
cow:translate(0.5,-0.5,-1.5)
cow:set_material(orange)
cow:scale(1,0.25,1)
--rocket:add_child(cow)

cow_poly:set_material(hide)
cow_poly:translate(0.5,-0.5,-1.5)
cow_poly:scale(0.25,0.0625,0.25)
cow_poly:rotate('z',-90)
cow_poly:rotate('y',-180)

rocket:add_child(cow_poly)

rocket:translate(-150,170,-450)
rocket:rotate('z',100)
--rocket:rotate('y',-45)
rocket:scale(25,100,25)

scene_root:add_child(rocket)




sun_light1 = gr.light({-500.0, 400.0, -750}, {1, 1, 1}, {1, 0, 0})
sun_light2 = gr.light({-500.0, 400.0, -750}, {1, 1, 1}, {1, 0, 0})
sun_light3 = gr.light({-500.0, 400.0, -750}, {1, 1, 1}, {1, 0, 0})
sun_light4 = gr.light({-500.0, 400.0, -750}, {1, 1, 1}, {1, 0, 0})
sun_light5 = gr.light({-500.0, 400.0, -750}, {1, 1, 1}, {1, 0, 0})
moon_light1 = gr.light({-200, -200, -100}, {0.5,0.5, 0.5}, {1, 0, 0})
moon_light2 = gr.light({-200, -200, -100}, {0.5,0.5, 0.5}, {1, 0, 0})

gr.render(scene_root, 'sample.png', 1000, 1000,
	  {0, 0, 800}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.1, 0.1, 0.1}, {sun_light1,sun_light2,sun_light3,sun_light4,sun_light5,moon_light1,moon_light2})
