all: cc/OneEuroFilter

test: cc/OneEuroFilter
	@./cc/OneEuroFilter > test.log
	@python py/OneEuroFilterComparator.py test.log 1e-4

clean:
	rm -f *~ */*~
	rm -f cc/OneEuroFilter
	rm -f py/*.pyc
	rm -f test.log
