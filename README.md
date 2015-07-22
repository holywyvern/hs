# Humming Script
Humming script contains a collection of modular pieces in c, to create an interpreted language

## Files included

### hs/array
Macros to implement dynamic arrays quickly.

### hs/bigdecimal
Contains an arbitrary precision library for decimal (floating point) types

### hs/bigint
Contains an arbitrary precision library for integer types

### hs/file
A file manipulation library with UTF-8 support for every platform.

### hs/gc (TODO)
Contains a generic garbage collector.

### hs/list
Contains an implementation of a double linked list

### hs/map
Macros to help the creation of maps (dictionaries of key-value pairs)

### hs/opcode
Contains the list of opcodes used by the machine

### hs/string
Contains implementations for ASCII/UTF-8 encoded string manipulations

### hs/thread
Contains a simple thread lock/unlock cross platform API.

### hs/types
Contains a list of types used by the language 

### hs/vm (TODO)
Contains the virtual machine for the language

## TODO

  * Implement a simple garbage collection.
  * Implement virtual machine
  * Implement dynamic lists
  * Implement dynamic sets
  * Implement dynamic maps
  * Implement strings
  * Implement lexer
  * Implement parser
  * Implement compiler
  * Implement bigdecimals
  * Implement the type system
  * Add more file APIs
  * Create an easy to use makefile/bakefile
  * Add documentation
  * Test cases
  * Examples

## How does the language is supposed to look at the future?

At the moment I make some test about syntax:

### Assignment

```ruby
#This is a line comment, multiline comments does not exist in Hs

# Assignment is done through the ':' operator

x: 23      # x now has the integer 23 on it
x: 8       # x now has the integer 8 on it
x: 'Hello' # x now has the string 'Hello'

```

Assignments are not expressions

```coffeescript

if x: something() { #wont work
 # ...
}

```

They can still be chained:

```coffeescript
x: y: z: 23 # x, y and z are now 23
```

And multiple assignments can be done in a single sentence

```coffeescript
x, y: y, x # common swap of values
```

You cannot chain this type of assignments:

```coffeescript
x, y: y, z: z, q # Illegal
```

And both sides always needs the same number of elements

```coffeescript

x, y: y # illegal

x: y, z # still illegal

```

### Literals

The language comes with many different literals:

#### Numeric literals

```ruby

x: 23     # Integer literals 
x: 0xF2D3 # Hexadecimal literals
x: 0o0734 # Octal literals
x: 0b1101 # Binary literals
x: 2'322  # Numbers can have ' as digit separators

x: 2.3    # This is a decimal literal
x: 2e3    # Exponential literals 

```

#### Container literals

```ruby
x: []        # This is an empty array
x: [1, 2, 3] # This is an array with three values

x: {}        # This is a map literal (associates key and value pairs)
x: { 'a' => 2, 'b' => 3 } # A map with some values
x: { a: 2, b: 3 } # If values are strings, they can be written like JSON

x: 1..200  # a range from 1 to 200 inclusive
x: 1...200 # A range from 1 to 200, but 200 is excluded
x: 1..10\2 # A range from 1 to 10, with 2 as it's step

x: 'Hello world' # An string literal
x: "Hello #{you}" # another string literal, but it adds interpolation with #{} 

```

#### Range literals

```ruby
x: 1..200  # a range from 1 to 200 inclusive
x: 1...200 # A range from 1 to 200, but 200 is excluded
x: 1..10\2 # A range from 1 to 10, with 2 as it's step
```

#### String literals

```ruby
x: 'Hello world' # An string literal
x: "Hello #{you}" # another string literal, but it adds interpolation with #{} 
```

#### Regular expression literals

```ruby
x: /Hello/     # match Hello (case sensitive)
x: /Hello/i    # match Hello (case insensitive)
x: /[Hh]ello/  # match both Hello and hello (case sensitive)
```

#### Lamda literals

In hs there is no thing as a method, methods have a this context like 
javascript. They have the same closure type as javascript also 

```ruby

#This lambda is inline
x: (x, y) -> x * y

# This lambda is a multiline function
x: (x, y) {
  return x * y
}

```

#### Empty objects

There is currently no empty object literal, but you may do something like

```coffeescript
x: new { 
  # Some code
}
```

The new is an operator to create objects based on others.
By default they clone Object

### Function calls

For calling functions, you have to pass the name of the arguments:

```ruby
do_something(with: 23, and: 32) 
```

Unless there is only one argument:

```ruby
set_something(32)
```
subscript getters/setters allow more than one value:

```ruby
x[1, 3] = 23
```

They don't need to have variable names

### The new keyword
The new keyword creates an object based on another, coping all of its properties

```coffeescript
x: new Array # copies the object Array
```

### Setting/Getting properties from objects.

```coffeescript
a : x.y # Gets property y from x
x.y : a * 2 # Sets property y of x as a * 2
```

### Scoped blocks

An object has an amount of private values, they can't be accesed from other
place than is not a method, or itself at creation

```coffeescript
o: new { 
  @x : 23 # This is a private property
}

o.@x # illegal

o.x # illegal, 'x' does not exists in 'o', so @x is effectively 'protected'

o.double_x: () -> @x * 2 # legal, "this" is o when called as o.double_x()

```

### Flow control

Standard if and while are easy to check

```coffeescript
if x > 3 -> 32 # in one line

if x > 3 {
 # multiline if
}

x: y > 5 ? 2 : 3 # Shorthand if

while (x) -> #Line while

while (x) {
  #...
}

```

For controls are different

```coffeescript

for id in object -> # it something like for each property of the object as id do...

for i in [1, 2, 3] {
 # objects can implement their own iteration method 
}

```

Case controls work with another equality

```coffeescript
#They always 'break'
case x {
 when 1...3 : #code if x is between 1 and 3 ( (1...3).includes(x) )
 when 2...5 : #code 
 else #default
}
```
