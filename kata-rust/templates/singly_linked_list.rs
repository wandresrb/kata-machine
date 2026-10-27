use std::marker::PhantomData;

use crate::types::List;

pub struct SinglyLinkedList<T> {
    // TODO: replace with your own fields (e.g. head: Option<Box<Node<T>>>, len: usize)
    _todo: PhantomData<T>,
}

impl<T> SinglyLinkedList<T> {
    pub fn new() -> Self {
        todo!()
    }
}

impl<T: Clone + PartialEq> List<T> for SinglyLinkedList<T> {
    fn len(&self) -> usize {
        todo!()
    }

    fn prepend(&mut self, item: T) {
        todo!()
    }

    fn append(&mut self, item: T) {
        todo!()
    }

    fn insert_at(&mut self, item: T, idx: usize) {
        todo!()
    }

    fn remove(&mut self, item: &T) -> Option<T> {
        todo!()
    }

    fn get(&self, idx: usize) -> Option<T> {
        todo!()
    }

    fn remove_at(&mut self, idx: usize) -> Option<T> {
        todo!()
    }
}
