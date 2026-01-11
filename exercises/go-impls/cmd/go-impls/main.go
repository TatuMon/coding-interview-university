package main

import (
	"fmt"

	"github.com/TatuMon/coding-interview-university/exercises/go-impls/pkg/vector"
)

func main() {
	myVector := vector.New[int](10)
	fmt.Printf("New vector: %s\n", myVector.SPrint())

	myVector.Push(1, 2, 3, 4, 5)
	fmt.Printf("After pushing 5 values: %s\n", myVector.SPrint())

	myVector.Insert(99, 2)
	fmt.Printf("After inserting 99 into index 2: %s\n", myVector.SPrint())

	myVector.Insert(88, 8)
	fmt.Printf("After inserting 88 into index 8: %s\n", myVector.SPrint())

	myVector.Insert(77, 15)
	fmt.Printf("After inserting 77 into index 15: %s\n", myVector.SPrint())
}
