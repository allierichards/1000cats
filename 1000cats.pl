#!/usr/bin/perl

use warnings;
use strict;

use String::Random;

my $target = "METHINKS IT IS LIKE A WEASEL";
my $characters = new String::Random;
$characters->{'S'} = ['A'..'Z', ' '];
my $generation = 1;
my $offspring_count = 1000;
my $chance = 2;
my $max_score;
my $max_ordinal;
my $max_offspring;
my $target_score = length($target);
my $c;
my $offspring_score;

my $survivor = $characters->randpattern("SSSSSSSSSSSSSSSSSSSSSSSSSSSS");
$max_score = getscore($survivor, $target);
$max_offspring = $survivor;
print "0: $max_offspring -- score: $max_score\n";
while ($max_score < $target_score)
{
  for ($c = 0; $c < $offspring_count; $c++)
  {
    $survivor = mutate($survivor, $chance);
    $offspring_score = getscore($survivor, $target);
    if ($offspring_score > $max_score)
    {
      $max_score = $offspring_score;
      $max_offspring = $survivor;
    }
  }
  print "$generation: $max_offspring -- score: $max_score\n";
  $generation++;
  $survivor = $max_offspring;
}

sub mutate
{
  my ($random, $chance) = @_;

  my $c;
  my $n;
  my $p;
  my $ret = $random;

  for ($c = 0; $c < length($random); $c++)
  {
    $n = rand(100);
    substr( $ret, $c, 1, $characters->randpattern("S") ) if $n <= $chance;
  }
  return $ret;
}

sub getscore
{
  my ($string1, $string2) = @_;

  my $length1 = length($string1);
  my $length2 = length($string2);
  my $c;
  my $score = 0;

  die "strings are not same length:\n$string1\n$string2\n can't continue\n" unless ($length1 == $length2);
  
  for ($c = 0; $c < $length1; $c++)
  {
    $score++ if ( substr($string1, $c, 1) eq substr($string2, $c, 1) );
  }
  return $score;
}
