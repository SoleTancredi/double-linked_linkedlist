/*
 * Employee.c
 *
 *  Created on: 15 dic. 2021
 *      Author: stanc
 */

#include "Employee.h"


Employee* employee_new()
{
	Employee *pBufferEmployee;
	pBufferEmployee = malloc(sizeof(Employee));

	return pBufferEmployee;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* salaryStr)
{
	Employee *pBufferEmployee;

	pBufferEmployee = employee_new();

	if(pBufferEmployee != NULL)
	{
       (*pBufferEmployee).id = atoi(idStr);
       strcpy((*pBufferEmployee).nombre, nombreStr);
       (*pBufferEmployee).horasTrabajadas = atoi(horasTrabajadasStr);
       (*pBufferEmployee).sueldo = atoi(salaryStr);
       return pBufferEmployee;
   	}
       return NULL;
}

void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int employee_setId(Employee* this,int id)
{
	int retorno = -1;

	if(this != NULL && id > 0)
	{
		(*this).id = id;
		retorno = 0;
	}

	return retorno;
}


int employee_getId(Employee* this,int* id)
{
   int retorno = -1;

   if(this != NULL && id != NULL)
   {
	   *id = (*this).id;
	   retorno = 0;
   }

   return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		strcpy((*this).nombre, nombre);
		retorno = 0;
	}
	return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, (*this).nombre);
		retorno = 0;
	}

	return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;

	if(this != NULL && horasTrabajadas > 0)
	{
		(*this).horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}

	return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;

	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = (*this).horasTrabajadas;
		retorno = 0;
	}

	return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;

	if(this != NULL && sueldo > 0)
	{
		(*this).sueldo = sueldo;
		retorno = 0;
	}

	return retorno;

}


int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;

	if(this != NULL && sueldo != NULL)
	{
		*sueldo = (*this).sueldo;
		retorno = 0;
	}

	return retorno;
}

void employee_showUnit(Employee* this)
{
	int id;
	char nombre[128];
	int sueldo;
	int horasT;

	if(this != NULL)
	{
		if(employee_getId(this,&id) == 0
		&& employee_getNombre(this,nombre) == 0
		&& employee_getHorasTrabajadas(this, &horasT) == 0
		&& employee_getSueldo(this, &sueldo) == 0)

		{
			printf("\n  %-6d|   %-16s    %-10d   %-10d \n", id, nombre, horasT, sueldo);
		}
		else
		{
			puts("\n aca hay un error en unit");
		}
	}
}

int employee_showList(LinkedList* this)
{
	int retorno = -1,cont=0;
	Employee* pAuxEmployee;


	if(this != NULL)
	{
		employee_posterList();
		for(int i = 0; i < ll_len(this); i++)
		{
			pAuxEmployee = ll_get(this, i);
			employee_showUnit(pAuxEmployee);
			cont++;
			retorno = 0;
		}
		printf("\n\t\t\t Cantidad de empleados: %d",cont);
	}

	return retorno;
}

int employee_mainModify()
{
	int option;

	printf("\n\t »»» MODIFICAR EMPLEADO «««");
	if(utn_getNumber(&option,"\n[1] NOMBRE."
			"\n[2] HORAS TRABAJADAS."
			"\n[3] SUELDO."
			"\n[4] MOSTRAR CAMBIOS REALIZADOS Y SALIR AL MENU PRINCIPAL."
			"\n » INGRESE UNA OPCION: "," × ERROR.", 1, 4, 1) == 0)
	{
		printf("\n »» Usted ha ingresado la opcion nº %d\n", option);
	}

	return option;
}

int employee_modify(Employee* this)
{
	int retorno = -1;
	int option;
	int rta1;
	int rta2;
	int rta3;
	Employee bufferEmployee;

	if(this != NULL)
	{
       do
       {
    	   option = employee_mainModify();

    	   switch(option)
    	   {
			   case 1:
				   if(utn_nombreOapellido(bufferEmployee.nombre, "\n »» INGRESE EL NOMBRE:",
						   "\n × ERROR. REINGRESE.", TAM_NAME,1) == 0)
				   {
					   printf("\n » Nuevo nombre ingresado es: [%s]\n", bufferEmployee.nombre);
					   if(utn_getNumber(&rta1,"\n » CONFIRMAR MODIFICACION ? "
										"\n  [1] SI "
										"\n  [2] NO ", "\n × Error.\n",1,2, 1) == 0)
					   {
						   if(rta1 == 1)
						   {
							   employee_setNombre(this, bufferEmployee.nombre);
							   printf("\n »» Correcto! ");
							   retorno =0;
						   }
					   }
				   }
					else
					{
						printf("\n »» NO SE REALIZO LA MODIFICACION.");
					}
				   break;
			   case 2:
				   if(utn_getNumber(&bufferEmployee.horasTrabajadas, "\n »» INGRESE LAS HORAS TRABAJADAS: ",
						   "\n × ERROR. REINGRESE.", 1 , 10000, 1) == 0)
				   {
					   printf("\n » Horas trabajadas ingresadas: [%d]\n", bufferEmployee.horasTrabajadas);
					   if(utn_getNumber(&rta2,"\n » CONFIRMAR MODIFICACION ? "
										"\n  [1] SI "
										"\n  [2] NO ", "\n × Error.\n",1,2, 1) == 0)
					   {
						   if(rta2 == 1)
						   {
							  employee_setHorasTrabajadas(this, bufferEmployee.horasTrabajadas);
							  printf("\n »» Correcto! ");
							  retorno =0;
						   }
					   }
				   }
				   else
					{
						printf("\n »» NO SE REALIZO LA MODIFICACION.");
					}
				   break;
			   case 3:
				   if(utn_getNumber(&bufferEmployee.sueldo, "\n »» INGRESE EL SUELDO: ",
				  						   "\n × ERROR. REINGRESE.", 0 , 200000, 1) == 0)
				   {
					   printf("\n » Sueldo ingresado: [%d]\n", bufferEmployee.sueldo);
					   if(utn_getNumber(&rta3,"\n » CONFIRMAR MODIFICACION ? "
										"\n  [1] SI "
										"\n  [2] NO ", "\n × Error.\n",1,2, 1) == 0)
					   {
						   if(rta3 == 1)
						   {
							  employee_setSueldo(this, bufferEmployee.sueldo);
							  printf("\n »» Correcto! ");
							  retorno =0;
						   }
					   }
				   }
				   else
				   {
						printf("\n »» NO SE REALIZO LA MODIFICACION.");
				   }

				   break;
			   case 4:
				   if(rta1 == 1 || rta2 == 1 || rta3 == 1)
				   {
					   employee_posterModified();
					   employee_showUnit(this);
					   printf("\n »»» Saliendo...");
				   }
				   else
				   {
						printf("\n »» NO HUBO CAMBIOS.\n");
						printf("\n »»» Saliendo...");
				   }
			       break;
    	   }

    	   retorno =0;

       }while(option != 4);

	}

	return retorno;
}

void employee_posterList()
{
	printf("\n\t  ## LISTADO DE EMPLEADOS ##");
	printf("\n__________________________________________________________\n");
	printf("\n  %-6s     %-14s%-14s    %-20s \n","ID ","NOMBRE ","HORAS TRAB. ","SUELDO ");
	printf("__________________________________________________________\n");
}

void employee_posterSelected()
{
	printf("\n\t  ## EMPLEADO ELEGIDO PARA MODIFICAR ##");
	printf("\n__________________________________________________________\n");
	printf("\n  %-6s     %-14s%-14s    %-20s \n","ID ","NOMBRE ","HORAS TRAB. ","SUELDO ");
	printf("__________________________________________________________\n");
}

void employee_posterModified()
{
	printf("\n\t  ## EMPLEADO MODIFICADO ##");
	printf("\n__________________________________________________________\n");
	printf("\n  %-6s     %-14s%-14s    %-20s \n","ID ","NOMBRE ","HORAS TRAB. ","SUELDO ");
	printf("__________________________________________________________\n");
}

void employee_posterPreview()
{
	printf("\n\t  ## VISTA PREVIA NUEVO EMPLEADO ##");
	printf("\n__________________________________________________________\n");
	printf("\n  %-6s     %-14s%-14s    %-20s \n","ID ","NOMBRE ","HORAS TRAB. ","SUELDO ");
	printf("__________________________________________________________\n");
}

int employee_add(Employee* this, int* id, char* nombre, int horasTrabajadas, int sueldo)
{
	int retorno = -1;

	if(this != NULL && id != NULL && nombre != NULL)
	{
		employee_setId(this, *id);
		employee_setNombre(this, nombre);
		employee_setHorasTrabajadas(this, horasTrabajadas);
		employee_setSueldo(this, sueldo);
		retorno = 0;
	}

	return retorno;
}

int employee_register(Employee* this, int id)
{
	int retorno = -1;
	int rtaSeguir;
	Employee bufferEmployee;

	if(this != NULL)
	{
		if(utn_nombreOapellido(bufferEmployee.nombre, "\n »» INGRESE EL NOMBRE: ",
		"\n × ERROR. REINGRESE.", TAM_NAME, 1) == 0
		&& utn_getNumber(&bufferEmployee.horasTrabajadas,"\n »» INGRESE LA HORAS TRABAJADAS: ",
		"\n × ERROR. REINGRESE. ",1, 60, 1) == 0
		&& utn_getNumber(&bufferEmployee.sueldo,"\n »» INGRESE EL SUELDO: ",
		"\n × ERROR. REINGRESE. " , 100, 1000000, 1) == 0)
		{
			employee_setId(&bufferEmployee, id);
			employee_posterPreview();
			employee_showUnit(&bufferEmployee);
			if(utn_getNumber(&rtaSeguir,"\n » DESEA CARGAR LOS DATOS ?"
					"\n  [1] SI "
					"\n  [2] NO ", "\n × ERROR.",1,2, 1) == 0)
			{
				if(rtaSeguir == 1)
				{
					if(employee_add(this, &id, bufferEmployee.nombre, bufferEmployee.horasTrabajadas, bufferEmployee.sueldo) == 0)
					{
						retorno = 0;
					}
				}
			}
		}
	}

	return retorno;
}

int employee_sortId(void* thisOne, void* thisTwo)
{
	int retorno = 0;
	Employee* pBuffer1;
	Employee* pBuffer2;

	pBuffer1 = thisOne;
	pBuffer2 = thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if((*pBuffer1).id < (*pBuffer2).id)
		{
			retorno = -1;
		}
		else
		{
			if((*pBuffer1).id > (*pBuffer2).id)
			{
				retorno = 1;
			}
		}
	}

	return retorno;
}

int employee_sortSalary(void* thisOne, void* thisTwo)
{
	int retorno = 0;
	Employee* pBuffer1;
	Employee* pBuffer2;

	pBuffer1 = thisOne;
	pBuffer2 = thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if((*pBuffer1).sueldo < (*pBuffer2).sueldo)
		{
			retorno = -1;
		}
		else
		{
			if((*pBuffer1).sueldo > (*pBuffer2).sueldo)
			{
				retorno = 1;
			}
		}
	}

	return retorno;
}

int employee_sortHours(void* thisOne, void* thisTwo)
{
	int retorno = 0;
	Employee* pBuffer1;
	Employee* pBuffer2;

	pBuffer1 = thisOne;
	pBuffer2 = thisTwo;

	if(thisOne != NULL && thisTwo != NULL)
	{
		if((*pBuffer1).horasTrabajadas< (*pBuffer2).horasTrabajadas)
		{
			retorno = -1;
		}
		else
		{
			if((*pBuffer1).horasTrabajadas > (*pBuffer2).horasTrabajadas)
			{
				retorno = 1;
			}
		}
	}

	return retorno;
}

int employee_sortNames(void* thisOne, void* thisTwo)
{
	int retorno = 0;
	Employee* pBuffer1;
	Employee* pBuffer2;

	pBuffer1 = thisOne;
	pBuffer2 = thisTwo;


	if(thisOne != NULL && thisTwo != NULL)
	{
		if(strcmp((*pBuffer1).nombre, (*pBuffer2).nombre) < 0)
		{
			retorno = -1;
		}
		else
		{
			if(strcmp((*pBuffer1).nombre, (*pBuffer2).nombre) > 0)
			{
				retorno = 1;
			}
		}
	}

	return retorno;
}

int employee_menuSortStandard()
{
	int eleccion;

	printf("\n\t\t >> MENU DE ORDENAMIENTO <<\n");
	if(utn_getNumber(&eleccion, "\n »»» ORDENAR POR CRITERIO: \n"
				"\n[1] Id."
				"\n[2] Alfabetico."
				"\n[3] Horas Trabajadas."
				"\n[4] Salario."
				"\n\n[5] Salir.\n"
				"\n »»» INGRESE UNA OPCION: "
				, "\n × ERROR. ", 1, 5, 1) == 0)
		{
			printf("\n »» Usted ha elegido la opcion nº %d \n", eleccion);
		}

	return eleccion;
}

int employee_menuSortWay()
{
	int opcion;

	if(utn_getNumber(&opcion, "\n »»» ORDENAR DE FORMA:\n"
			"\n[1] Ascendente."
			"\n[2] Descendente"
			"\n »»» INGRESE UNA OPCION: ","\n × ERROR.",1 , 2, 1) == 0)
	{
		printf("\n »» Aguarde un momento... \n");
	}

	return opcion;
}


