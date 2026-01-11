package vector

import (
	"fmt"
	"strings"
)

type Vector[T comparable] struct {
	arr []T // Length and capacity is already handled by the slice type
}

func New[T comparable](capacity uint) Vector[T] {
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

	fmt.Fprintf(&b, " len=%d", len(v.arr))
	fmt.Fprintf(&b, " cap=%d", cap(v.arr))

	return b.String()
}

func (v *Vector[T]) Len() uint {
	return uint(len(v.arr))
}

func (v *Vector[T]) Cap() uint {
	return uint(cap(v.arr))
}

func (v *Vector[T]) At(index uint) T {
	return v.arr[index]
}

func (v *Vector[T]) Set(value T, index uint) {
	v.arr[index] = value
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

func (v *Vector[T]) Prepend(value T) {
	v.Insert(value, 0)
}

func (v *Vector[T]) Pop() T {
	popped := v.arr[len(v.arr)-1]
	v.arr = v.arr[:len(v.arr)-1]

	return popped
}

func (v *Vector[T]) Delete(index uint) {
	if index >= uint(len(v.arr)) {
		return
	}

	rightSide := v.arr[index+1:]
	copy(v.arr[index:], rightSide)
}

func (v *Vector[T]) Remove(value T) {
	for i, j := range v.arr {
		if j == value {
			v.Delete(uint(i))
		}
	}
}

func (v *Vector[T]) First(value T) int {
	for i, j := range v.arr {
		if j == value {
			return i
		}
	}

	return -1
}
