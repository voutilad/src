# Tests for tr, but the test file is not utf8.

BEGIN {
    chdir 't' if -d 't';
    require './test.pl';
    set_up_inc('../lib');
}

plan tests => 1;

{ # This test is malloc senstive.  Right now on some platforms anyway, space
  # for the final \xff needs to be mallocd, and that's what caused the
  # problem, because the '-' had already been parsed and was later added
  # without making space for it
    fresh_perl_is('print "\x8c" =~ y o\x{100}Č????-?oo', "1", { },
                    'RT #134067 heap-buffer-overflow in S_scan_const');

}

1;
