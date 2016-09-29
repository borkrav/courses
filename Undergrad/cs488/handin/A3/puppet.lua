rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)


torsoJoint = gr.joint('torsoJoint', {0, 0, 0}, {0, 0, 0} )
rootnode:add_child(torsoJoint)

torsoJointSphere = gr.sphere('torsoJointSphere')
--torsoJoint:add_child(torsoJointSphere)
torsoJointSphere:set_material(blue)
torsoJointSphere:scale(0.1, 0.1, 3)

torso = gr.sphere('torso')
torsoJoint:add_child(torso)
torso:set_material(red)
torso:scale(1, 2, 1)



torsoToShoulders = gr.joint('torsoToShoulders', {0, 0, 0}, {0, 0, 0} )
torsoToShoulders:translate(0, 2.0, 0)
torsoJoint:add_child(torsoToShoulders)

torsoToShouldersSphere = gr.sphere('torso')
--torsoToShoulders:add_child(torsoJointSphere)
torsoToShouldersSphere:set_material(blue)
torsoToShouldersSphere:scale(0.1, 0.1, 3)

shoulders = gr.sphere('shoulders')
torsoToShoulders:add_child(shoulders)
shoulders:set_material(red)
shoulders:scale(2.2, 0.5, 0.7)

torsoToHips = gr.joint('torsoToHips', {0, 0, 0}, {0, 0, 0} )
torsoToHips:translate(0, -2, 0)
torsoJoint:add_child(torsoToHips)

torsoToHipsSphere = gr.sphere('torsoToHipsSphere')
--torsoToHips:add_child(torsoToHipsSphere)
torsoToHipsSphere:set_material(blue)
torsoToHipsSphere:scale(0.1, 0.1, 3)

hips = gr.sphere('hips')
torsoToHips:add_child(hips)
hips:set_material(red)
hips:scale(1.0, 0.9, 1)


hipToLeftThigh = gr.joint('hipToLeftThigh', {-130, 0, 0}, {0, 0, 0} )
hipToLeftThigh:translate(-0.5, -0.5, 0)
torsoToHips:add_child(hipToLeftThigh)

hipToLeftThighSphere = gr.sphere('hipToLeftThighSphere')
--hipToLeftThigh:add_child(hipToLeftThighSphere)
hipToLeftThighSphere:set_material(blue)
hipToLeftThighSphere:scale(0.1, 0.1, 3)


leftThigh = gr.sphere('leftThigh')
hipToLeftThigh:add_child(leftThigh)
leftThigh:set_material(red)
leftThigh:scale(0.5, 1, 0.5)
leftThigh:translate(-0.5, -0.8, 0)

hipToRightThigh = gr.joint('hipToRightThigh', {-130, 0, 0}, {0, 0, 0} )
hipToRightThigh:translate(0.5, -0.5, 0)
torsoToHips:add_child(hipToRightThigh)

rightThigh = gr.sphere('rightThigh')
hipToRightThigh:add_child(rightThigh)
rightThigh:set_material(red)
rightThigh:scale(0.5, 1, 0.5)
rightThigh:translate(0.5, -0.8, 0)

leftKnee = gr.joint('leftKnee', {0, 0, 130}, {0, 0, 0} )
leftKnee:translate(-0.25, -1.5, 0)
hipToLeftThigh:add_child(leftKnee)

leftKneeSphere = gr.sphere('leftKneeSphere')
--leftKnee:add_child(leftKneeSphere)
leftKneeSphere:set_material(blue)
leftKneeSphere:scale(0.1, 0.1, 3)

leftCalf = gr.sphere('leftCalf')
leftKnee:add_child(leftCalf)
leftCalf:set_material(red)
leftCalf:translate(0, -1, 0)
leftCalf:scale(0.5, 1, 0.5)

rightKnee = gr.joint('rightKnee', {0, 0, 130}, {0, 0, 0} )
rightKnee:translate(0.25, -1.5, 0)
hipToRightThigh:add_child(rightKnee)

rightCalf = gr.sphere('rightCalf')
rightKnee:add_child(rightCalf)
rightCalf:set_material(red)
rightCalf:translate(0, -1, 0)
rightCalf:scale(0.5, 1, 0.5)

leftAnkle = gr.joint('leftAnkle', {-30, 0, 45}, {0, 0, 0} )
leftAnkle:translate(0, -2, 0)
leftKnee:add_child(leftAnkle)
leftAnkle:rotate('x', 270)
leftAnkle:rotate('z', -90)

leftAnkleSphere = gr.sphere('leftAnkleSphere')
--leftAnkle:add_child(leftKneeSphere)
leftAnkleSphere:set_material(blue)
leftAnkleSphere:scale(0.1, 0.1, 3)


leftFoot = gr.sphere('leftFoot')
leftAnkle:add_child(leftFoot)
leftFoot:set_material(red)
leftFoot:translate(0, -0.5, 0)
leftFoot:scale(0.5, 0.7, 0.3)

rightAnkle = gr.joint('rightAnkle', {-30, 0, 45}, {0, 0, 0} )
rightAnkle:translate(0, -2, 0)
rightKnee:add_child(rightAnkle)
rightAnkle:rotate('x', 270)
rightAnkle:rotate('z', 90)

rightFoot = gr.sphere('rightFoot')
rightAnkle:add_child(rightFoot)
rightFoot:set_material(red)
rightFoot:translate(0, -0.5, 0)
rightFoot:scale(0.5, 0.7, 0.3)





leftShoulder = gr.joint('leftShoulder', {-180, 0, 90}, {0, 0, 0} )
leftShoulder:translate(-2, 0, 0)
torsoToShoulders:add_child(leftShoulder)

leftShoulderSphere = gr.sphere('leftShoulderSphere')
--leftShoulder:add_child(leftShoulderSphere)
leftShoulderSphere:set_material(blue)
leftShoulderSphere:scale(0.1, 0.1, 3)

leftBicep = gr.sphere('leftBicep')
leftShoulder:add_child(leftBicep)
leftBicep:set_material(red)
leftBicep:translate(0, -1, 0)
leftBicep:scale(0.5, 1, 0.5)

rightShoulder = gr.joint('rightShoulder', {-180, 0, 90}, {0, 0, 0} )
rightShoulder:translate(2, 0, 0)
torsoToShoulders:add_child(rightShoulder)

rightBicep = gr.sphere('rightBicep')
rightShoulder:add_child(rightBicep)
rightBicep:set_material(red)
rightBicep:translate(0, -1, 0)
rightBicep:scale(0.5, 1, 0.5)

leftElbow = gr.joint('leftElbow', {-130, 0, 0}, {0, 0, 0} )
leftElbow:translate(0, -1.6, 0)
leftShoulder:add_child(leftElbow)

leftElblowSphere = gr.sphere('leftElblowSphere')
--leftElbow:add_child(leftElblowSphere)
leftElblowSphere:set_material(blue)
leftElblowSphere:scale(0.1, 0.1, 3)

leftForearm = gr.sphere('leftForearm')
leftElbow:add_child(leftForearm)
leftForearm:set_material(red)
leftForearm:translate(0, -0.9, 0)
leftForearm:scale(0.4, 0.7, 0.4)

rightElbow = gr.joint('rightElbow', {-130, 0, 0}, {0, 0, 0} )
rightElbow:translate(0, -1.6, 0)
rightShoulder:add_child(rightElbow)

rightForearm = gr.sphere('rightForearm')
rightElbow:add_child(rightForearm)
rightForearm:set_material(red)
rightForearm:translate(0, -0.9, 0)
rightForearm:scale(0.4, 0.7, 0.4)

leftWrist = gr.joint('leftWrist', {-90, 0, 90}, {0, 0, 0} )
leftWrist:translate(0, -1.4, 0)
leftElbow:add_child(leftWrist)

leftWristSphere = gr.sphere('leftWristSphere')
--leftWrist:add_child(leftElblowSphere)
leftWristSphere:set_material(blue)
leftWristSphere:scale(0.1, 0.1, 3)

leftHand = gr.sphere('leftHand')
leftWrist:add_child(leftHand)
leftHand:set_material(red)
leftHand:translate(0, -0.6, 0)
leftHand:scale(0.5, 0.5, 0.5)

rightWrist = gr.joint('rightWrist', {-90, 0, 90}, {0, 0, 0} )
rightWrist:translate(0, -1.4, 0)
rightElbow:add_child(rightWrist)

rightHand = gr.sphere('rightHand')
rightWrist:add_child(rightHand)
rightHand:set_material(red)
rightHand:translate(0, -0.6, 0)
rightHand:scale(0.5, 0.5, 0.5)







shouldersToNeck = gr.joint('shouldersToNeck', {-45, 0, 45}, {0, 0, 0} )
shouldersToNeck:translate(0, 0, 0)
torsoToShoulders:add_child(shouldersToNeck)



neck = gr.sphere('neck')
shouldersToNeck:add_child(neck)
neck:set_material(red)
neck:translate(0, 0.6, 0)
neck:scale(0.5, 0.7, 0.5)


neckToHead = gr.joint('neckToHead', {-45, 0, 45}, {-90, 0, 90} )
neckToHead:translate(0, 1, 0)
shouldersToNeck:add_child(neckToHead)


neckToHeadSphere = gr.sphere('neckToHeadSphere')
--neckToHead:add_child(neckToHeadSphere)
neckToHeadSphere:set_material(blue)
neckToHeadSphere:scale(0.1, 0.1, 3)

head = gr.sphere('head')
neckToHead:add_child(head)
head:set_material(red)
head:translate(0, 1, 0)
head:scale(1, 1, 1)

faceJoint = gr.joint('neckToHead', {0 ,0 ,0}, {0, 0, 0} )
faceJoint:translate(0, 1, 0)
neckToHead:add_child(faceJoint)

leftEye = gr.sphere('leftEye')
faceJoint:add_child(leftEye)
leftEye:set_material(red)
leftEye:translate(-0.6, 0.2, 0.8)
leftEye:scale(0.2, 0.2, 0.2)

rightEye = gr.sphere('rightEye')
faceJoint:add_child(rightEye)
rightEye:set_material(red)
rightEye:translate(0.6, 0.2, 0.8)
rightEye:scale(0.2, 0.2, 0.2)

nose = gr.sphere('nose')
faceJoint:add_child(nose)
nose:set_material(red)
nose:translate(0, -0.2, 0.9)
nose:scale(0.25, 0.25, 0.25)


return rootnode
