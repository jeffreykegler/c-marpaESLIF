use strict;
use warnings FATAL => 'all';

package MarpaX::ESLIF::Value;
use MarpaX::ESLIF::Registry;     # Maintains thread-safe single ESLIF registry

my $CLONABLE = 0;


# ABSTRACT: MarpaX::ESLIF's value

# AUTHORITY

# VERSION

=head1 DESCRIPTION

MarpaX::ESLIF::Value is a possible step after a MarpaX::ESLIF::Recognizer instance is created.

=head1 SYNOPSIS

  my $eslifValue = MarpaX::ESLIF::Value->new($eslifRecognizer, $valueInterface);

The value interface is used to get parse tree valuation.

=head1 METHODS

=head2 MarpaX::ESLIF::Value->new($eslifRecognizer, $valueInterface)

  my $eslifValue = MarpaX::ESLIF::Value->new($eslifRecognizer, $valueInterface);

Returns a value instance, noted C<$eslifValue> later. Parameters are:

=over

=item C<$eslifRecognizer>

MarpaX::ESLIF:Recognizer object instance. Required.

=item C<$valueInterface>

An object implementing L<MarpaX::ESLIF::Value::Interface> methods. Required.

=back

=cut

sub new {
    my $class = shift;
    
    return MarpaX::ESLIF::Registry::new($class, $CLONABLE, undef, \&MarpaX::ESLIF::Value::allocate, \&MarpaX::ESLIF::Value::dispose, @_)
}

=head2 $eslifValue->value()

Returns a boolean indicating if there a value to retrieve via the valueInterface's getResult() method.

=head1 SEE ALSO

L<MarpaX::ESLIF::Value::Interface>

=head1 NOTES

L<MarpaX::ESLIF::Value> cannot be reused across threads.

=cut

sub DESTROY {
    goto &MarpaX::ESLIF::Registry::DESTROY
}

1;
