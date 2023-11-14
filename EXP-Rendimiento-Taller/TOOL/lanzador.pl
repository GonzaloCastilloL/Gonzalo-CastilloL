#!/usr/bin/perl   
=for comment
/***************************************************************
*   Fecha: Octubre 2023
*   Autor: J. Corredor
*   Materia: Computación de Alto Rendimiento
*   Maestría de Inteligencia Artificial
*   Pontificia Universidad Javeriana
*   Objetivo: Herramienta para automatizar proceso de ejecución
*             por lotes. 
****************************************************************/
=cut


if(@ARGV[0]){
		$numRep = "$ARGV[0]";
}else{
		usage();
}

print "\n Repeticiones de la experimentación: $numRep \n\n";


$path0 = `pwd`;
chomp($path0);
$T = index($path0,"T")-1;
$Path = substr($path0,0,$T);
print "$Path \n";


@Ejecutables = ("MM1c"); 
@cores = ("1");
@VectorSize= ("100","200","400","600","800");

foreach $exe (@Ejecutables){ 
    foreach $ves (@VectorSize){
        foreach $c (@cores) {
            $file = "$Path/"."Soluciones/"."$exe"."-Size"."$ves"."-core"."$c";
            #print "$file \n"; #Nombre del fichero
            for($i=0; $i<$numRep;  $i++){
                system("$Path/BIN/$exe $ves $c 0   >> $file");
                print "$Path/BIN/$exe $ves $c 0  \n" ;
            }
            close($file);
        }
    }
}
exit(1);


sub MedCOV {
          my($array1, $array2) = @_;
          @p_vector = @{$array1};
          @s_vector = @{$array2};
          $suma  = 0; $std  = 0;
          $media = 0; $coef = 0;
          $times   = $s_vector[0];
          for ($j=0; $j < $times; $j++) {
              $suma  += $p_vector[$j];
              $suma2 += $p_vector[$j]**2;
          }
          if ($j>0) {
              $media = $suma/$j;
          }
          for ($j=0; $j < $times; $j++) {
              $std += ($p_vector[$j]-$media)**2;
          }
          $cov = sqrt($std/($times-1));
          if ($media > 0) {
              $coef = 100*$cov/$media;
          }
            splice(@p_vector, 0, $times);
 	  }

sub usage()
	{
		print "\n tst.pl: Uso incorrecto\n\n";
		print "\t revisar entradas o directorio de almacenaje \n\n\n";
		exit(1);
	}
       


