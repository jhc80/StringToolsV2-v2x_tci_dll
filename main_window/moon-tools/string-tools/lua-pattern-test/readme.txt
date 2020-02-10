lua的字符串模式

x: (where x is not one of the magic characters ^$()%.[]*+-?) 
	represents the character x itself.
	这里的x代表任意的一个字符，除了一些特殊的字符 ^$()%.[]*+-?
	表示x字符本身。
	
. : (a dot) represents all characters.
. : 可以表示所有的字符
   
%a: represents all letters.
%a: 表示所有的字母。

%c: represents all control characters.
%c: 表示所有的控制字符

%d: represents all digits.
%d: 表示所有的数字

%g: represents all printable characters except space.
%g: 表示所有的可打印字符，但是不包括空格

%l: represents all lowercase letters.
%l: 表示所有的小写字母

%p: represents all punctuation characters.
%p: 表示所有的标点符号

%s: represents all space characters.
%s: 表示所有的空白字符

%u: represents all uppercase letters.
%u: 表示所有的大写字母

%w: represents all alphanumeric characters.
%w: 表示所有的字母和数字

%x: represents all hexadecimal digits.
%x: 表示所有的十六进制的字母

%x: (where x is any non-alphanumeric character) represents the character x. 
    This is the standard way to escape the magic characters. Any non-alphanumeric 
    character (including all punctuation characters, even the non-magical) can be 
	preceded by a '%' when used to represent itself in a pattern.
%x: (这里的x表示所有的非字母和数字的字符)	代表x字符本身。
    这是标准的转义特殊字符的方法。任何非字母数字的字符（包括所有的标点符号或者
	是非特殊字符）都可以在前面加上一个%来表示它自身。
	
[set]: represents the class which is the union of all characters in set. A range of 
	characters can be specified by separating the end characters of the range, in 
	ascending order, with a '-'. All classes %x described above can also be used as 
	components in set. All other characters in set represent themselves. For example,
	[%w_] (or [_%w]) represents all alphanumeric characters plus the underscore,
	[0-7] represents the octal digits, and [0-7%l%-] represents the octal digits plus 
	the lowercase letters plus the '-' character.
	You can put a closing square bracket in a set by positioning it as the first character 
	in the set. You can put an hyphen in a set by positioning it as the first or the last 
	character in the set. (You can also use an escape for both cases.)
[set]: 表示其中所有字符的集合。可以使用两个字符中间加上一个- 表示一个字符的范围，
    比如 a-z 表示所有的a到z的字符集合，0-9表示所有0到9之间的字符，注意两个开始和
	结束的字符要是升序排列。转义字符也可以用在集合当中，比如%-表示减号本身。其余
	的字符就表示它们本身，例如[%w_] (or [_%w]) 就表示所有的字符数字再加上一个下滑线
	[0-7] 表示一个8进制的数字，[0-7%l%-]表示一个8进制的数字加上一个小写字母在加上一个
	减号。
	您可以将方括号放在第一个字符中，将其放在集合中在集合中。 您可以将连字符放置在
	集合中，方法是将其放在第一个或最后一个集合中的字符。 
	（您也可以在两种情况下都使用转义符。）

The interaction between ranges and classes is not defined. Therefore, 
patterns like [%a-z] or [a-%%] have no meaning.
范围和类之间的交互未定义。 因此，
[％a-z]或[a-%%]之类的模式没有意义。

[^set]: represents the complement of set, where set is interpreted as above.
For all classes represented by single letters (%a, %c, etc.), the corresponding 
uppercase letter represents the complement of the class. For instance, %S 
represents all non-space characters.
[^ set]：表示集合的补集，其中集合的解释如上。
对于由单个字母表示的所有类（％a，％c等），对应的
大写字母表示该类的补集。 例如 %S代表所有非空格字符。

The definitions of letter, space, and other character groups depend on the 
current locale. In particular, the class [a-z] may not be equivalent to %l.
字母，空格和其他字符组的定义取决于
当前语言环境。 特别地，[a-z]可能不等同于％l。

Pattern Item:
模式

A pattern item can be
a single character class, which matches any single character in the class;

a single character class followed by '*', which matches zero or more repetitions 
    of characters in the class. These repetition items will always match the longest 
	possible sequence;

单个字符后跟 '*' ,表示匹配零个或多个重复的这个字符。 采用的是最长匹配原则。

a single character class followed by '+', which matches one or more repetitions 
    of characters in the class. These repetition items will always match the longest 
	possible sequence;
单个字符后跟 '+'，表示匹配一个或多个重复的这个字符。 采用的是最长匹配原则。

a single character class followed by '-', which also matches zero or more repetitions 
    of characters in the class. Unlike '*', these repetition items will always match the 
	shortest possible sequence;
单个字符后跟 '-'，表示匹配零个或多个重复的这个字符。 采用的是最短匹配原则。

a single character class followed by '?', which matches zero or one occurrence of 
    a character in the class. It always matches one occurrence if possible;
单个字符后跟 '？'，表示匹配零个或一个字符。 总是首先匹配一个字符的情况。
	
%n, for n between 1 and 9; such item matches a substring equal to the n-th 
    captured string (see below);
％n，n在1到9之间； 此类项目匹配等于第n个子字符串
    捕获的字符串（见下文）；

%bxy, where x and y are two distinct characters; such item matches strings that 
    start with x, end with y, and where the x and y are balanced. This means that, 
	if one reads the string from left to right, counting +1 for an x and -1 for a y, 
	the ending y is the first y where the count reaches 0. For instance, the item 
	%b() matches expressions with balanced parentheses.

％bxy，其中x和y是两个不同的字符； 这样的项目匹配的字符串
     以x开头，以y结尾，并且x和y处于平衡状态。 这意味着，
    如果从左到右读取该字符串，则x计数为+ 1，y计数为-1，
    结束点y是计数达到0的第一个y。例如，该项
    ％b（）匹配带有平衡括号的表达式。

%f[set], a frontier pattern; such item matches an empty string at any position 
    such that the next character belongs to set and the previous character does 
	not belong to set. The set set is interpreted as previously described. The beginning
	and the end of the subject are handled as if they were the character '\0'.
％f[set]，一种边界模式； 这个模式在任何位置都匹配一个空字符串
     这个位置的下一个字符属于集合而前一个字符不属于集合。 集合的解释如前所述。 
     文本的开始和结尾被当作字符“ \ 0”来处理。

Pattern:

A pattern is a sequence of pattern items. A caret '^' at the beginning of a pattern 
    anchors the match at the beginning of the subject string. A '$' at the end of a 
	pattern anchors the match at the end of the subject string. At other positions, 
	'^' and '$' have no special meaning and represent themselves.

模式是一系列模式项。 在模式开头的插入符号'^'将匹配字符串的开头。 
末尾的“ $”模式将匹配字符串的末尾。 在其他位置，
“ ^”和“ $”没有特殊含义，它们代表自己。

Captures:
捕获

A pattern can contain sub-patterns enclosed in parentheses; they describe captures. 
    When a match succeeds, the substrings of the subject string that match captures 
	are stored (captured) for future use. Captures are numbered according to their left 
	parentheses. For instance, in the pattern "(a*(.)%w(%s*))", the part of the string 
	matching "a*(.)%w(%s*)" is stored as the first capture (and therefore has number 1);
	the character matching "." is captured with number 2, and the part matching "%s*"
	has number 3.

模式可以包含用括号括起来的子模式； 他们描述了捕获。
     匹配成功后，将捕获匹配的字符串的子字符串存储（捕获）以备将来使用。 
捕获的内容按其左侧括号编号。 例如，在模式 "(a*(.)%w(%s*))" 中，字符串的一部分
匹配“ a*(.)%w(%s*)”作为第一个捕获存储（因此具有编号1）；
匹配“.”的字符 用数字2捕获，并且匹配“％s*”的部分有数字3。

As a special case, the empty capture () captures the current string position (a number).
 For instance, if we apply the pattern "()aa()" on the string "flaaap", there will be two 
 captures: 3 and 5.
 作为一种特殊情况，空捕获（）捕获当前字符串位置（一个数字）。
  例如，如果我们在字符串“ flaaap”上应用模式“（）aa（）”，则会有两个
  捕获：3和5。