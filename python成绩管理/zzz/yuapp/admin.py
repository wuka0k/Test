from django.contrib import admin
from . import models
from import_export.admin import ImportExportModelAdmin
from . models import Classer
from import_export import resources
# Register your models here.

# admin.site.register(models.Classer)
admin.site.register(models.UserExtension)


class ClasserResource(resources.ModelResource):
    class Meta:
        model = Classer
@admin.register(Classer)
class ClasserAdmin(ImportExportModelAdmin):
    resource_class = ClasserResource
    pass