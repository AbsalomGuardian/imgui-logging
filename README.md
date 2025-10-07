# imgui-starter

Logging System build Oct 5th 2025 Absalom Ranelletti

Functionality includes a fixed log window, with the provided methods for hiding the log window commented out. By fixed, it can be resized and moved around, but currently not completely hidden, only collapsed. A visible bool was still implemented in case the feature needs to be added latter. The getInstance function was reworked using GeekForGeek's tutorial about singletons. 

There are three methods for writing messages to the log. LogInfo is for basic technical messages, while LogGameEvent is for more flavorful messages that are supposed to be from the opposing AI. There's also LogError for non-fatal errors we want to show the user. Currently that's just the exception state for opening a file to write to.


Needed to ask questions about what a singleton was and if the writing to file feature should be modal or retroactive. I was given an option, and went with modal reasoning it would be easier because I didn't have to create a buffer. Needed to ask for clarification on how to store the log messages, because my inital attempt didn't didn't use a vector and was flawed.



Google's AI overview feature was used to answer extremely specific questions along the lines of "ImGui set window size" to learn which method I should use for it. There was still plently of looking at documentation for questions that couldn't be answered with 1-3 lines of code. 

Made on WindowsOS.

After Oct 7th:
Changed the logger to hold all the messages in a vector, and now while there's no way to filter what level of messages are seen, all messages do still have a level associated with them. Now the ImGui::Begin() and ImGui::End() are completely inside Logger::ShowLogWindow(). Write to file functionality is now retroactive and a single button, recording all the messages stored in the logger. There is also a functioning "write test message" button now. Window has been made moveable and resizable, so the fact it can end up outside of the main viewport isn't a problem.
