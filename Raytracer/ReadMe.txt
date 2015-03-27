Name: Mangesh Gandhi; Login: cs184-dh
Partner: Ankur Kansal
Platform: Windows
Source Code: Ankur Kansal has submitted on Windows




--------------------------------------------------------------------------------------------------------------------------------------------------


Used Cimg to write pixels to
Used an idea from scratchapixel for ray sphere intersection. The quadratic formula wasn't working for some reason.
http://stackoverflow.com/questions/14846905/transposing-a-matrix-c modified the code for a transpose given here

Cimg library had some problems in visual Studio. Had to change some settings (https://social.msdn.microsoft.com/Forums/vstudio/en-US/c1b08c0a-a803-41c3-ac8c-84eba3be1ddb/faq-cannot-convert-from-const-char-to-lpctstr?forum=vclanguage):
Change your project configuration to use multibyte strings. Press ALT+F7 to open the properties, and navigate to Configuration Properties > General. Switch Character Set to "Use Multi-Byte Character Set". 
