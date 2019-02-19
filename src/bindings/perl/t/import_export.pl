package MyRecognizerInterface;
use strict;
use diagnostics;

sub new                    { my ($pkg, $characterStream) = @_; bless { characterStream => $characterStream }, $pkg }
sub read                   { 1 }
sub isEof                  { 1 }
sub isCharacterStream      { $_[0]->{characterStream} // 1 }
sub encoding               { }
sub data                   { " " } # One byte
sub isWithDisableThreshold { 0 }
sub isWithExhaustion       { 0 }
sub isWithNewline          { 1 }
sub isWithTrack            { 1 }

package MyValueInterface;
use strict;
use diagnostics;

sub new                { my ($pkg) = @_; bless { result => undef }, $pkg }
sub isWithHighRankOnly { 1 }
sub isWithOrderByRank  { 1 }
sub isWithAmbiguous    { 0 }
sub isWithNull         { 0 }
sub maxParses          { 0 }
sub getResult          { $_[0]->{result} }
sub setResult          { $_[0]->{result} = $_[1] }
sub perl_proxy         { $_[1] }

package main;
use strict;
use warnings FATAL => 'all';
use Test::Deep::NoTest qw/cmp_details deep_diag/;
use Log::Log4perl qw/:easy/;
use Log::Any::Adapter;
use Log::Any qw/$log/;
use Math::BigInt;
use Math::BigFloat;

our @input;
BEGIN {
    use utf8;
    @input =
        (
         undef,
         "XXX",
         ["\xa0\xa1", 0],
         ["\xf0\x28\x8c\x28", 0],
         "Ḽơᶉëᶆ ȋṕšᶙṁ ḍỡḽǭᵳ ʂǐť ӓṁệẗ, ĉṓɲṩḙċťᶒțûɾ ấɖḯƥĭṩčįɳġ ḝłįʈ, șếᶑ ᶁⱺ ẽḭŭŝḿꝋď ṫĕᶆᶈṓɍ ỉñḉīḑȋᵭṵńť ṷŧ ḹẩḇőꝛế éȶ đꝍꞎôꝛȇ ᵯáꞡᶇā ąⱡîɋṹẵ.",
         ["Ḽơᶉëᶆ ȋṕšᶙṁ ḍỡḽǭᵳ ʂǐť ӓṁệẗ, ĉṓɲṩḙċťᶒțûɾ ấɖḯƥĭṩčįɳġ ḝłįʈ, șếᶑ ᶁⱺ ẽḭŭŝḿꝋď ṫĕᶆᶈṓɍ ỉñḉīḑȋᵭṵńť ṷŧ ḹẩḇőꝛế éȶ đꝍꞎôꝛȇ ᵯáꞡᶇā ąⱡîɋṹẵ.", 0],
         ["Ḽơᶉëᶆ ȋṕšᶙṁ ḍỡḽǭᵳ ʂǐť ӓṁệẗ, ĉṓɲṩḙċťᶒțûɾ ấɖḯƥĭṩčįɳġ ḝłįʈ, șếᶑ ᶁⱺ ẽḭŭŝḿꝋď ṫĕᶆᶈṓɍ ỉñḉīḑȋᵭṵńť ṷŧ ḹẩḇőꝛế éȶ đꝍꞎôꝛȇ ᵯáꞡᶇā ąⱡîɋṹẵ.", 1],
         0,
         1,
         -32768,
         32767,
         -32769,
         32768,
         2.34,
         1.6e+308,
         Math::BigFloat->new("6.78E+9"),
         Math::BigInt->new("6.78E+9"),
         { one => "one", two => "two", perltrue => 1, true => $MarpaX::ESLIF::true }
        );
}
use Test::More tests => 1 + scalar(@input) + 2;
use Test::More::UTF8;
use open qw( :utf8 :std );

BEGIN { require_ok('MarpaX::ESLIF') }
push(@input, $MarpaX::ESLIF::true, $MarpaX::ESLIF::false);
#
# Init log
#
our $defaultLog4perlConf = '
log4perl.rootLogger              = TRACE, Screen
log4perl.appender.Screen         = Log::Log4perl::Appender::Screen
log4perl.appender.Screen.stderr  = 0
log4perl.appender.Screen.layout  = PatternLayout
log4perl.appender.Screen.layout.ConversionPattern = %d %-5p %6P %m{chomp}%n
';
Log::Log4perl::init(\$defaultLog4perlConf);
Log::Any::Adapter->set('Log4perl');

my $grammar = q{
event ^perl_input = predicted perl_input

perl_output ::= lua_proxy  action => perl_proxy
lua_proxy   ::= perl_input action => ::lua->lua_proxy
perl_input  ::= PERL_INPUT action => perl_proxy
PERL_INPUT    ~ [^\s\S]

<luascript>
  function table_print (tt, indent, done)
    done = done or {}
    indent = indent or 0
    if type(tt) == "table" then
      for key, value in pairs (tt) do
        io.write(string.rep (" ", indent)) -- indent it
        if type (value) == "table" and not done [value] then
          done [value] = true
          io.write(string.format("[%s] => table\n", tostring (key)));
          io.write(string.rep (" ", indent+4)) -- indent it
          io.write("(\n");
          table_print (value, indent + 7, done)
          io.write(string.rep (" ", indent+4)) -- indent it
          io.write(")\n");
        else
          io.write(string.format("[%s] => %s\n",
              tostring (key), tostring(value)))
        end
      end
    else
      io.write(tostring(tt) .. "\n")
    end
  end

  io.stdout:setvbuf('no')

  function lua_proxy(value)
    io.write("lua_proxy: ")
    table_print(value)
    return value
  end
</luascript>
};

my $eslif = MarpaX::ESLIF->new($log);
my $eslifGrammar = MarpaX::ESLIF::Grammar->new($eslif, $grammar);

foreach my $inputArray (@input) {
    my ($input, $characterStream) = (ref($inputArray) || '') eq 'ARRAY' ? @{$inputArray} : ($inputArray, 1);
    my $eslifRecognizerInterface = MyRecognizerInterface->new($characterStream);
    my $eslifRecognizer = MarpaX::ESLIF::Recognizer->new($eslifGrammar, $eslifRecognizerInterface);
    $eslifRecognizer->scan(1); # Initial events
    $eslifRecognizer->lexemeRead('PERL_INPUT', $input, 1, 1);
    my $eslifValueInterface = MyValueInterface->new();
    my $eslifValue = MarpaX::ESLIF::Value->new($eslifRecognizer, $eslifValueInterface);
    $eslifValue->value();
    my $value = $eslifValueInterface->getResult;
    my ($ok, $stack) = cmp_details($value, $input);
    diag(deep_diag($stack)) unless (ok($ok, "import/export of " . (ref($input) ? ref($input) : (defined($input) ? "$input" : 'undef'))));
}

done_testing();

1;
