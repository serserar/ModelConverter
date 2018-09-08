/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "md5command.h"
/*
-force	Ignored
-game	Specify the mod name, which is where the relative paths are defined from. This should get set automatically in 1.2
-rename [joint name] [new name]	Rename a joint
-prefix [joint prefix]	 If you have multiple characters/objects in your scene, you can give them each their own prefix so the exporter can distinguish which goes to which. Example: ZSEC_ IMP_ ENV_
-parent [joint name] [new parent]	Reparent a joint
-sourcedir [directory]	Tell exporter where to get files from
-destdir [directory]	Tell exporter where to put files after export
-dest [filename]	Give a new name to the file you are exporting. Default will be same name as the maya file.
-range [start frame] [end frame]	Frame range for what you would like to export Example: -range 1 10
-cycleStart [first frame of cycle]	 Shift the cycle to start on a different frame. Example: frame 1 has left foot forward and frame 10 has right foot forward. So if you would like your cycle to start with right foot forward do -cycleStart 10 and it will shift the cycle
-scale [scale amount]	Scale up or down your character during export. Example: -scale 2 will double the size of the character. Scaled up from the origin.
-align [joint name]	Will align your animation to a certain bone.
-rotate [yaw]	Allow you to manually rotate your animation. Example: -rotate 90
-nomesh	
-clearorigin	
-clearoriginaxis	
-ignorescale	Ignore any scales you may have on some bones.
-xyzprecision [precision]	Will take even tiny movements (translations) into consideration if you make this # lower. Default will try and compress down the animations getting rid of tiny movements.
-quatprecision [precision]	Will take even tiny movements (rotations) into consideration if you make this # lower. Default will try and compress down the animations getting rid of tiny movements.
-jointthreshold [min joint weight]	
-skipmesh [name of mesh]	Allows you to skip certain models during export (can only be used by itself)
-keepmesh [name of mesh]	Allows you to keep only a certain model during export (can only be used by itself)
-jointgroup [group name]
[joint1] [joint2]...[joint n]	
-group [group name]	Add the list of groups to export (these don't affect the hierarchy)
-keep [joint name]	Add joints that are kept whether they're used by a mesh or not 
 */
