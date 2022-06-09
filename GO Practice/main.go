package main

import "fmt"

//constant blocks
const (
	first  = 1
	second = "second"
	third  = iota     // value of third will be 2. iota initializes based on the position (0,1,2...)
	fourth = iota + 6 // result is 9 (3+6)
	fifth             //result is 10. It takes previos expression value and adds iota
)

func iota_demo() {
	fmt.Println(first, second, third, fourth, fifth)
}

func array_demo() {
	var arr [3]int
	arr[0] = 1
	arr[1] = 2
	arr[2] = 3
	fmt.Println(arr)

	//implicit initialization
	arr2 := [3]int{1, 2, 3}
	fmt.Println(arr2)
}

//slice built on top of array
func slice_demo() {
	arr := [3]int{1, 2, 3}
	slice := arr[:]
	fmt.Println(slice)
	//slice is poining to elements in the array. Any changes in slice will be reflected in array and vice versa
	slice[2] = 50
	arr[1] = 25
	fmt.Println(slice)

	slice1 := []int{10, 20, 30} // No size is specified. Underlying array is managed by GO
	fmt.Println(slice1)

	//Unlike arrays slice is dynamic. Meaning we can change the size of the slice.
	slice1 = append(slice1, 21, 22, 23)
	fmt.Println(slice1)

	slice3 := slice1[1:] // similar to python. slice with start and end position
	slice4 := slice1[:2]

	fmt.Println(slice3, slice4)

}

func main() {
	//fmt.Println("Hello my first Go")
	//primitive data types
	var i int
	i = 10
	fmt.Println(i)

	var f float32 = 3.14
	fmt.Println(f)

	firstname := "Basavaraj"
	fmt.Println(firstname)

	b := true
	fmt.Println(b)

	c := complex(3, 4)
	fmt.Println(c)

	r, im := real(c), imag(c)
	fmt.Println(r, im)

	//Pointers. // By default its nil
	//Pointer airthmetic is not allowed in GO.
	var fName *string = new(string)
	*fName = "Ainapur"
	fmt.Println(*fName)

	ptr := &firstname
	fmt.Println(ptr, *ptr)

	firstname = "shweta"
	fmt.Println(*ptr)

	//constants, Have to be declared and defined at same time
	const pi = 3.142
	fmt.Println(pi)

	//complier can implicitly interpret the type of constants
	const constC = 3
	fmt.Println(constC + 3)   // Here constC is interpreted as int
	fmt.Println(constC + 1.5) // Here constC is interpreted as float

	//we can restrict this implicit interpretation
	const constD int = 4
	//fmt.Println(constD + 2.4) // compiler error
	fmt.Println(float32(constD) + 2.4) //By using conversion operator

	iota_demo()
	array_demo()
	slice_demo()
}
