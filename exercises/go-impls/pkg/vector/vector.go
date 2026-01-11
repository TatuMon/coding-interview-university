package vector

import (
	"fmt"
	"strings"
)

type Vector[T any] struct {
	arr []T // Length and capacity is already handled by the slice type
}

func New[T any](capacity uint) Vector[T] {
	return Vector[T]{
		arr: make([]T, 0, capacity),
	}
}

func (v *Vector[T]) SPrint() string {
	b := strings.Builder{}
	fmt.Fprint(&b, "[")
	for i, s := range v.arr {
		fmt.Fprint(&b, s)
		if i != len(v.arr)-1 {
			fmt.Fprint(&b, ", ")
		}
	}
	fmt.Fprint(&b, "]")

	return b.String()
}

func (v *Vector[T]) Push(values ...T) {
	v.arr = append(v.arr, values...)
}

func (v *Vector[T]) Insert(value T, index uint) {
	if index > uint(len(v.arr)) {
		indicesToAdd := index - uint(len(v.arr)) + 1
		v.arr = append(v.arr, make([]T, indicesToAdd)...)
		v.arr[index] = value
		return
	}

	replacedVal := v.arr[index]

	if index == uint(len(v.arr)) {
		v.arr = append(v.arr, replacedVal)
		v.arr[index] = value
	}

	leftSide := v.arr[:index]
	newRightSide := append([]T{value, replacedVal}, v.arr[index+1:]...)

	v.arr = append(leftSide, newRightSide...)
}
