@page Set-Up
@tableofcontents

@section VS Visual Studio
<ul>
	<li>To setup Visual Studio 2019 for OpenGl</li>
	<li>Download Visual Studio 2019 from [here](https://visualstudio.microsoft.com/downloads/) </li>
	<li>Then just follow the instructions to install it</li>
	<li>Make a new empty project in the required directory name it accordingly</li>
	<li>Make the main file.cpp in the source code</li>
	<li>Locate the project in your windows explorer</li>
	<li>Next to add the libraries GLFW and GLUT</li>
	<li>To add them add a new folder called Dependencies to the solution directory of the project</li>
</ul>
<!---
To setup Visual Studio 2019 for OpenGl  

Download Visual Studio 2019 from [here](https://visualstudio.microsoft.com/downloads/)  
Then just follow the instructions to install it  
  
Make a new empty project in the required directory name it accordingly  
Make the main file.cpp in the source code   

Locate the project in your windows explorer 
Next to add the libraries GLFW and GLUT  
To add them add a new folder called Dependencies to the solution directory of the project  
-->

@section glfw GLFW
<ul>
	<li>Download the 32-binaries from [here](https://www.glfw.org/download.html)</li>
	<li>Make a new folder in the Dependencies Folder called GLFW</li>
	<li>Extract the zip file to this folder</li>
	<li>Open the properties of the solution and in C/C++ General in Additional Include Directories add $(SolutionDir)Dependencies\GLFW\include;</li>
	<li>In the Linker General in Additional Library Directories add $(SolutionDir)Dependencies\GLFW\lib-vc2015;</li>
	<li>In Linker Input in Additional Dependencies add glfw3.lib;</li>
</ul>
<img src="ss1.jpeg" alt="drawing" width="500" /><br><br>
<!--
Download the 32-binaries from [here](https://www.glfw.org/download.html)

Make a new folder in the Dependencies Folder called GLFW
Extract the zip file to this folder

Open the properties of the solution and in C/C++ General in Additional Include Directories add $(SolutionDir)Dependencies\GLFW\include;

In the Linker General in Additional Library Directories add $(SolutionDir)Dependencies\GLFW\lib-vc2015; 

In Linker Input in Additional Dependencies add glfw3.lib;
-->
@section glut GLUT

<ul>
	<li>Download the binaries from [here](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)</li>
	<li>Make a new folder in the Dependencies Folder called GLUT</li>
	<li>Extract the zip file to this folder</li>
	<li>Open the properties of the solution and in C/C++ General in Additional Include Directories add $(SolutionDir)Dependencies\GLFW\include;</li>
	<li>In the Linker General in Additional Library Directories add (SolutionDir)Dependencies\GLUT\include;</li>
	<li>In Linker Input in Additional Dependencies add glut32.lib;</li>
	<li>Copy glut32.dll to the working folder in the project </li>
</ul>
<img src="ss2.jpeg" alt="drawing" width="500" /><br><br>
<img src="ss3.jpeg" alt="drawing" width="500" /><br><br>

<!--
Download the binaries from [here](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)

Make a new folder in the Dependencies Folder called GLUT
Extract the zip file to this folder

Open the properties of the solution and in C/C++ General in Additional Include Directories add $(SolutionDir)Dependencies\GLFW\include;

In the Linker General in Additional Library Directories add (SolutionDir)Dependencies\GLUT\include;

In Linker Input in Additional Dependencies add glut32.lib;
copy glut32.dll to the working folder in the project 
-->

