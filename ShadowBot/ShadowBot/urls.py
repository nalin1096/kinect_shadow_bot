from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'ShadowBot.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', 'ShadowBot.views.index', name='home'),
    url(r'^post/(?P<post_id>\d+)/$', 'ShadowBot.views.post'),
)
