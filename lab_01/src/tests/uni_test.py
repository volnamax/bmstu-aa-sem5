import unittest

from algorithms import *


class TestLevenshtein(unittest.TestCase):
    def test_equal_strings(self):
        self.assertEqual(levenshtein("abc", "abc"), 0)

    def test_empty_strings(self):
        self.assertEqual(levenshtein("", ""), 0)

    def test_insertion(self):
        self.assertEqual(levenshtein("cat", "cats"), 1)

    def test_deletion(self):
        self.assertEqual(levenshtein("book", "boo"), 1)

    def test_substitution(self):
        self.assertEqual(levenshtein("kitten", "sitting"), 3)

    def test_long_strings(self):
        self.assertEqual(levenshtein("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxy"), 1)

    def test_unicode_characters(self):
        self.assertEqual(levenshtein("café", "coffee"), 4)

    def test_unicode_characters_(self):
        self.assertEqual(levenshtein("book", "back"), 2)

    def test_equal_russian_words(self):
        self.assertEqual(levenshtein("мама", "мама"), 0)

    def test_different_russian_words(self):
        self.assertEqual(levenshtein("мама", "папа"), 2)

    def test_long_russian_words(self):
        self.assertEqual(levenshtein("красивый", "красный"), 2)

    def test_one_sym_eng(self):
        self.assertEqual(levenshtein("a", "b"), 1)

    def test_one_sym_eq_eng(self):
        self.assertEqual(levenshtein("a", "a"), 0)

    def test_rus_cat_scat(self):
        self.assertEqual(levenshtein("кот", "скат"), 2)

    def test_rus_fritnd(self):
        self.assertEqual(levenshtein("друзья", "рдузия"), 3)

    def test_rus_train(self):
        self.assertEqual(levenshtein("вагон", "гонки"), 4)

    def test_rus_slaves(self):
        self.assertEqual(levenshtein("бар", "раб"), 2)

    def test_rus_elephan(self):
        self.assertEqual(levenshtein("слон", "стол"), 2)

class TestDamerauLevenshtein(unittest.TestCase):
    def test_equal_strings(self):
        self.assertEqual(damerauLevenshtein("abc", "abc"), 0)

    def test_empty_strings(self):
        self.assertEqual(damerauLevenshtein("", ""), 0)

    def test_insertion(self):
        self.assertEqual(damerauLevenshtein("cat", "cats"), 1)

    def test_deletion(self):
        self.assertEqual(damerauLevenshtein("book", "boo"), 1)

    def test_substitution(self):
        self.assertEqual(damerauLevenshtein("kitten", "sitting"), 3)

    def test_long_strings(self):
        self.assertEqual(damerauLevenshtein("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxy"), 1)

    def test_unicode_characters(self):
        self.assertEqual(damerauLevenshtein("café", "coffee"), 4)

    def test_unicode_characters_(self):
        self.assertEqual(damerauLevenshtein("back", "book"), 2)

    def test_equal_russian_words(self):
        self.assertEqual(damerauLevenshtein("мама", "мама"), 0)

    def test_different_russian_words(self):
        self.assertEqual(damerauLevenshtein("мама", "папа"), 2)

    def test_long_russian_words(self):
        self.assertEqual(damerauLevenshtein("красивый", "красный"), 2)

    def test_one_sym_eng(self):
        self.assertEqual(damerauLevenshtein("a", "b"), 1)

    def test_one_sym_eq_eng(self):
        self.assertEqual(damerauLevenshtein("a", "a"), 0)

    def test_rus_cat_scat(self):
        self.assertEqual(damerauLevenshtein("кот", "скат"), 2)

    def test_rus_fritnd(self):
        self.assertEqual(damerauLevenshtein("друзья", "рдузия"), 2)

    def test_rus_train(self):
        self.assertEqual(damerauLevenshtein("вагон", "гонки"), 4)

    def test_rus_slaves(self):
        self.assertEqual(damerauLevenshtein("бар", "раб"), 2)

    def test_rus_elephan(self):
        self.assertEqual(damerauLevenshtein("слон", "стол"), 2)


class TestDamerauLevenshteinRecurs(unittest.TestCase):
    def test_equal_strings(self):
        self.assertEqual(damerauLevenshteinRecurs("abc", "abc"), 0)

    def test_empty_strings(self):
        self.assertEqual(damerauLevenshteinRecurs("", ""), 0)

    def test_insertion(self):
        self.assertEqual(damerauLevenshteinRecurs("cat", "cats"), 1)

    def test_deletion(self):
        self.assertEqual(damerauLevenshteinRecurs("book", "boo"), 1)

    def test_substitution(self):
        self.assertEqual(damerauLevenshteinRecurs("kitten", "sitting"), 3)

    def test_unicode_characters(self):
        self.assertEqual(damerauLevenshteinRecurs("café", "coffee"), 4)

    def test_unicode_characters_(self):
        self.assertEqual(damerauLevenshteinRecurs("back", "book"), 2)

    def test_equal_russian_words(self):
        self.assertEqual(damerauLevenshteinRecurs("мама", "мама"), 0)

    def test_different_russian_words(self):
        self.assertEqual(damerauLevenshteinRecurs("мама", "папа"), 2)

    def test_long_russian_words(self):
        self.assertEqual(damerauLevenshteinRecurs("красивый", "красный"), 2)

    def test_one_sym_eng(self):
        self.assertEqual(damerauLevenshteinRecurs("a", "b"), 1)

    def test_one_sym_eq_eng(self):
        self.assertEqual(damerauLevenshteinRecurs("a", "a"), 0)

    def test_rus_cat_scat(self):
        self.assertEqual(damerauLevenshteinRecurs("кот", "скат"), 2)

    def test_rus_fritnd(self):
        self.assertEqual(damerauLevenshteinRecurs("друзья", "рдузия"), 2)

    def test_rus_train(self):
        self.assertEqual(damerauLevenshteinRecurs("вагон", "гонки"), 4)

    def test_rus_slaves(self):
        self.assertEqual(damerauLevenshteinRecurs("бар", "раб"), 2)

    def test_rus_elephan(self):
        self.assertEqual(damerauLevenshteinRecurs("слон", "стол"), 2)

class TestDLRC(unittest.TestCase):
    def test_equal_strings(self):
        self.assertEqual(dLRC("abc", "abc"), 0)

    def test_empty_strings(self):
        self.assertEqual(dLRC("", ""), 0)

    def test_insertion(self):
        self.assertEqual(dLRC("cat", "cats"), 1)

    def test_deletion(self):
        self.assertEqual(dLRC("book", "boo"), 1)

    def test_substitution(self):
        self.assertEqual(dLRC("kitten", "sitting"), 3)

    def test_unicode_characters(self):
        self.assertEqual(dLRC("café", "coffee"), 4)

    def test_unicode_characters_(self):
        self.assertEqual(dLRC("back", "book"), 2)

    def test_equal_russian_words(self):
        self.assertEqual(dLRC("мама", "мама"), 0)

    def test_different_russian_words(self):
        self.assertEqual(dLRC("мама", "папа"), 2)

    def test_long_russian_words(self):
        self.assertEqual(dLRC("красивый", "красный"), 2)

    def test_one_sym_eng(self):
        self.assertEqual(dLRC("a", "b"), 1)

    def test_one_sym_eq_eng(self):
        self.assertEqual(dLRC("a", "a"), 0)

    def test_rus_cat_scat(self):
        self.assertEqual(dLRC("кот", "скат"), 2)

    def test_rus_fritnd(self):
        self.assertEqual(dLRC("друзья", "рдузия"), 2)

    def test_rus_train(self):
        self.assertEqual(dLRC("вагон", "гонки"), 4)

    def test_rus_slaves(self):
        self.assertEqual(dLRC("бар", "раб"), 2)

    def test_rus_elephan(self):
        self.assertEqual(dLRC("слон", "стол"), 2)


if __name__ == '__main__':
    unittest.main()
