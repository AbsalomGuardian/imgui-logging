# imgui-starter

Logging System build Oct 5th 2025 Absalom Ranelletti

Functionality includes a fixed log window, with the provided methods for hiding the log window commented out. A visible bool was still implemented in case the feature needs to be added latter. The getInstance function was reworked using GeekForGeek's tutorial about singletons. 

There are two methods for writing messages to the log. LogInfo is for basic technical messages, while LogGameEvent is for more flavorful messages that are supposed to be from the opposing AI. 

The creation of the logger object had to be moved from GameStartUp() to RenderGame(). A bunch of set-up methods I was told I needed to include for ImGui in the documentation I looked at was added to GameStartUp().

Needed to ask questions about what a singleton was and if the writing to file feature should be modal or retroactive. I was given an option, and went with modal reasoning it would be easier because I didn't have to create a buffer. 



Google's AI overview feature was used to answer extremely specific questions along the lines of "ImGui set window size" to learn which method I should use for it. There was still plently of looking at documentation for questions that couldn't be answered with 1-3 lines of code. 

Made on WindowsOS.

After Oct 5th:
In this current build, because of what I feel is some kind of fundamental misunderstanding of IMGui, I can't figure out how to make a button to write to the log after it is pressed, using the LogGameEvent or LogInfo functions, because from the prespective of ShowLogWindow, there is no logger object. As side effect of this is I can't test LogGameEvent and LogInfo's ability to write to file without a handler function that should not be mixed with the button. This is part of my fundamental problem of despite all my playing with frames I don't know how to create multiple windows. Ideally this will be fixed this upcoming week. I also want to make it so my windows with stay inside the program window even when I move it. 

