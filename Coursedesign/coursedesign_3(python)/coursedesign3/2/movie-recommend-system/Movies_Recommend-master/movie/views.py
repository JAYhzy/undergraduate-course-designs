import csv
import time
import os.path
from math import sqrt
from django.contrib import messages
from django.db.models import Avg, Count, Max
from django.http import HttpResponse, request
from django.shortcuts import render, redirect, reverse
from .forms import RegisterForm, LoginForm, CommentForm
from django.views.generic import View, ListView, DetailView
from .models import User, Movie, Genre, Movie_rating, Movie_similarity, Movie_hot

# DO NOT MAKE ANY CHANGES
BASE = os.path.dirname(os.path.abspath(__file__))

class IndexView(ListView):#用于展示一个对象列表的视图
    model = Movie
    template_name = 'movie/index.html'  #渲染视图
    paginate_by = 15  #分页
    context_object_name = 'movies' #将模型对象列表存储在上下文中的变量名为 'movies'
    ordering = 'imdb_id'
    page_kwarg = 'p'

    def get_queryset(self):
        # 返回前1000部电影
        return Movie.objects.filter(imdb_id__lte=1000)

    def get_context_data(self, *, object_list=None, **kwargs):
        #用于获取并返回视图的上下文数据。
        context = super(IndexView, self).get_context_data(*kwargs)
        paginator = context.get('paginator')
        page_obj = context.get('page_obj')
        pagination_data = self.get_pagination_data(paginator, page_obj)
        context.update(pagination_data)
        # print(context)
        return context

    def get_pagination_data(self, paginator, page_obj, around_count=2):
        #用于计算分页相关信息
        current_page = page_obj.number

        if current_page <= around_count + 2:
            left_pages = range(1, current_page)
            left_has_more = False
        else:
            left_pages = range(current_page - around_count, current_page)
            left_has_more = True

        if current_page >= paginator.num_pages - around_count - 1:
            right_pages = range(current_page + 1, paginator.num_pages + 1)
            right_has_more = False
        else:
            right_pages = range(current_page + 1, current_page + 1 + around_count)
            right_has_more = True
        return {
            'left_pages': left_pages,
            'right_pages': right_pages,
            'current_page': current_page,
            'left_has_more': left_has_more,
            'right_has_more': right_has_more
        }


class PopularMovieView(ListView):
    model = Movie_hot
    template_name = 'movie/hot.html'
    paginate_by = 15
    context_object_name = 'movies'
    page_kwarg = 'p'

    def get_queryset(self):
        # movie_hot__rating_number 的最大值进行注解，并按照该字段降序排列，以获取热门电影列表。
        hot_movies=Movie_hot.objects.all().values("movie_id")
        movies=Movie.objects.filter(id__in=hot_movies).annotate(nums=Max('movie_hot__rating_number')).order_by('-nums')
        return movies

    def get_context_data(self, *, object_list=None, **kwargs):

        context = super(PopularMovieView, self).get_context_data(*kwargs)
        paginator = context.get('paginator')
        page_obj = context.get('page_obj')
        pagination_data = self.get_pagination_data(paginator, page_obj)
        context.update(pagination_data)
        # print(context)
        return context

    def get_pagination_data(self, paginator, page_obj, around_count=2):
        current_page = page_obj.number

        if current_page <= around_count + 2:
            left_pages = range(1, current_page)
            left_has_more = False
        else:
            left_pages = range(current_page - around_count, current_page)
            left_has_more = True

        if current_page >= paginator.num_pages - around_count - 1:
            right_pages = range(current_page + 1, paginator.num_pages + 1)
            right_has_more = False
        else:
            right_pages = range(current_page + 1, current_page + 1 + around_count)
            right_has_more = True
        return {
            'left_pages': left_pages,
            'right_pages': right_pages,
            'current_page': current_page,
            'left_has_more': left_has_more,
            'right_has_more': right_has_more
        }


class TagView(ListView):
    model = Movie
    template_name = 'movie/tag.html'
    paginate_by = 15
    context_object_name = 'movies'
    # ordering = 'movie_rating__score'
    page_kwarg = 'p'

    def get_queryset(self):
        #获取所有电影对象，并返回索引在100到200之间的电影对象
        if 'genre' not in self.request.GET.dict().keys():
            movies = Movie.objects.all()
            return movies[100:200]
        else:
            movies = Movie.objects.filter(genre__name=self.request.GET.dict()['genre'])
            print(movies)
            return movies[:100]

    def get_context_data(self, *, object_list=None, **kwargs):
        context = super(TagView, self).get_context_data(*kwargs)
        if 'genre' in self.request.GET.dict().keys():
            genre = self.request.GET.dict()['genre']
            context.update({'genre': genre})
        paginator = context.get('paginator')
        page_obj = context.get('page_obj')
        pagination_data = self.get_pagination_data(paginator, page_obj)
        context.update(pagination_data)
        return context

    def get_pagination_data(self, paginator, page_obj, around_count=2):
        current_page = page_obj.number

        if current_page <= around_count + 2:
            left_pages = range(1, current_page)
            left_has_more = False
        else:
            left_pages = range(current_page - around_count, current_page)
            left_has_more = True

        if current_page >= paginator.num_pages - around_count - 1:
            right_pages = range(current_page + 1, paginator.num_pages + 1)
            right_has_more = False
        else:
            right_pages = range(current_page + 1, current_page + 1 + around_count)
            right_has_more = True
        return {
            'left_pages': left_pages,
            'right_pages': right_pages,
            'current_page': current_page,
            'left_has_more': left_has_more,
            'right_has_more': right_has_more
        }


class SearchView(ListView):
    model = Movie
    template_name = 'movie/search.html'
    paginate_by = 15
    context_object_name = 'movies'
    # ordering = 'movie_rating__score'
    page_kwarg = 'p'

    def get_queryset(self):
        # 获取请求中的 'keyword' 参数，并根据电影名中包含该关键字的电影进行过滤。
        movies = Movie.objects.filter(name__icontains=self.request.GET.dict()['keyword'])
        print(movies)
        return movies

    def get_context_data(self, *, object_list=None, **kwargs):
        # self.genre=self.request.GET.dict()['genre']
        context = super(SearchView, self).get_context_data(*kwargs)
        paginator = context.get('paginator')
        page_obj = context.get('page_obj')
        pagination_data = self.get_pagination_data(paginator, page_obj)
        context.update(pagination_data)
        context.update({'keyword': self.request.GET.dict()['keyword']})
        return context

    def get_pagination_data(self, paginator, page_obj, around_count=2):
        current_page = page_obj.number

        if current_page <= around_count + 2:
            left_pages = range(1, current_page)
            left_has_more = False
        else:
            left_pages = range(current_page - around_count, current_page)
            left_has_more = True

        if current_page >= paginator.num_pages - around_count - 1:
            right_pages = range(current_page + 1, paginator.num_pages + 1)
            right_has_more = False
        else:
            right_pages = range(current_page + 1, current_page + 1 + around_count)
            right_has_more = True
        return {
            'left_pages': left_pages,
            'right_pages': right_pages,
            'current_page': current_page,
            'left_has_more': left_has_more,
            'right_has_more': right_has_more
        }


# 注册视图
class RegisterView(View):
    #继承自 Django 的 View 类，用于处理 GET 和 POST 请求。
    def get(self, request):
        return render(request, 'movie/register.html')

    def post(self, request):
        form = RegisterForm(request.POST)
        if form.is_valid():
            #   保存
            form.save()
            return redirect(reverse('movie:index'))
        else:
            # 表单验证失败，重定向到注册页面
            errors = form.get_errors()
            for error in errors:
                messages.info(request, error)
            print(form.errors.get_json_data())
            return redirect(reverse('movie:register'))


# 登录视图
class LoginView(View):
    def get(self, request):
        return render(request, 'movie/login.html')

    def post(self, request):
        print(request.POST)
        form = LoginForm(request.POST)
        if form.is_valid():
            name = form.cleaned_data.get('name')
            pwd = form.cleaned_data.get('password')
            user = User.objects.filter(name=name, password=pwd).first()
            if user:
                # 登录成功，在session 里面加上当前用户的id，作为标识
                request.session['user_id'] = user.id
                return redirect(reverse('movie:index'))
                if remember:
                    # 设置为None，则表示使用全局的过期时间
                    request.session.set_expiry(None)
                else:
                    request.session.set_expiry(0)
            else:
                print('用户名或者密码错误')
                messages.info(request, '用户名或者密码错误!')
                return redirect(reverse('movie:login'))
        else:
            print("error!!!!!!!!!!!")
            errors = form.get_errors()
            for error in errors:
                messages.info(request, error)
            print(form.errors.get_json_data())
            return redirect(reverse('movie:login'))

def UserLogout(request):
    # 登出，立即停止会话
    request.session.set_expiry(-1)
    return redirect(reverse('movie:index'))


class MovieDetailView(DetailView):#用于展示单个对象的详细信息
    '''电影详情页面'''
    model = Movie
    template_name = 'movie/detail.html'
    # 上下文对象的名称
    context_object_name = 'movie'

    def get_context_data(self, **kwargs):
        # 重写获取上下文方法，增加评分参数
        context = super().get_context_data(**kwargs)
        # 判断是否登录用
        login = True
        try:
            user_id = self.request.session['user_id']
        except KeyError as e:
            login = False  # 未登录

        # 获得电影的pk
        pk = self.kwargs['pk']
        movie = Movie.objects.get(pk=pk)

        if login:
            # 已经登录，获取当前用户的历史评分数据
            user = User.objects.get(pk=user_id)

            rating = Movie_rating.objects.filter(user=user, movie=movie).first()
            # 默认值
            score = 0
            comment = ''
            if rating:
                score = rating.score
                comment = rating.comment
            context.update({'score': score, 'comment': comment})

        similarity_movies = movie.get_similarity()
        # 获取与当前电影最相似的电影
        context.update({'similarity_movies': similarity_movies})
        # 判断是否登录，没有登录则不显示评分页面
        context.update({'login': login})

        return context

    # 接受评分表单,pk是当前电影的数据库主键id
    def post(self, request, pk):
        url = request.get_full_path()
        form = CommentForm(request.POST)
        if form.is_valid():
            # 获取分数和评论
            score = form.cleaned_data.get('score')
            comment = form.cleaned_data.get('comment')
            print(score, comment)
            # 获取用户和电影
            user_id = request.session['user_id']
            user = User.objects.get(pk=user_id)
            movie = Movie.objects.get(pk=pk)

            # 更新一条记录
            rating = Movie_rating.objects.filter(user=user, movie=movie).first()
            if rating:
                # 如果存在则更新
                # print(rating)
                rating.score = score
                rating.comment = comment
                rating.save()
                # messages.info(request,"更新评分成功！")
            else:
                print('记录不存在')
                # 如果不存在则添加
                rating = Movie_rating(user=user, movie=movie, score=score, comment=comment)
                rating.save()
            messages.info(request, "评论成功!")

        else:
            # 表单没有验证通过
            messages.info(request, "评分不能为空!")
        return redirect(reverse('movie:detail', args=(pk,)))


class RatingHistoryView(DetailView):
    '''用户详情页面'''
    model = User
    template_name = 'movie/history.html'
    # 上下文对象的名称
    context_object_name = 'user'

    def get_context_data(self, **kwargs):
        # 这里要增加的对象：当前用户过的电影历史
        context = super().get_context_data(**kwargs)
        user_id = self.request.session['user_id']
        user = User.objects.get(pk=user_id)
        # 获取ratings即可
        ratings = Movie_rating.objects.filter(user=user)

        context.update({'ratings': ratings})
        return context


def delete_recode(request, pk):
    #用于处理删除评分记录的功能。
    print(pk)
    movie = Movie.objects.get(pk=pk)
    user_id = request.session['user_id']
    print(user_id)
    user = User.objects.get(pk=user_id)
    rating = Movie_rating.objects.get(user=user, movie=movie)
    print(movie, user, rating)
    rating.delete()
    messages.info(request, f"删除 {movie.name} 评分记录成功！")
    # 跳转回评分历史
    return redirect(reverse('movie:history', args=(user_id,)))


class RecommendMovieView(ListView):
    model = Movie
    template_name = 'movie/recommend.html'
    paginate_by = 15
    context_object_name = 'movies'
    ordering = 'movie_rating__score'
    page_kwarg = 'p'

    def __init__(self):
        #构造函数，初始化了一些常量和变量
        super().__init__()
        # 最相似的20个用户
        self.K = 20
        # 推荐出10个
        self.N = 10
        # 存放当前用户评分过的电影querySet
        self.cur_user_movie_qs = None

    def get_user_sim(self):
        #获取与当前用户相似度最高的 K 个用户
        # 用户相似度字典，格式为{ user_id1:val , user_id2:val , ... }
        user_sim_dct = dict()
        '''获取用户之间的相似度,存放在user_sim_dct中'''
        # 获取当前用户
        cur_user_id = self.request.session['user_id']
        cur_user = User.objects.get(pk=cur_user_id)
        # 获取其它用户
        other_users = User.objects.exclude(pk=cur_user_id)

        self.cur_user_movie_qs = Movie.objects.filter(user=cur_user)

        # 计算当前用户与其他用户评分过的电影交集数
        for user in other_users:
            # 记录感兴趣的数量
            user_sim_dct[user.id] = len(Movie.objects.filter(user=user) & self.cur_user_movie_qs)

        # 按照key排序value，返回K个最相近的用户
        print("user similarity calculated!")
        # 格式是 [ (user, value), (user, value), ... ]
        return sorted(user_sim_dct.items(), key=lambda x: -x[1])[:self.K]

    def get_recommend_movie(self, user_lst):
        #基于相似用户列表，获取推荐的电影列表。
        #遍历相似用户列表，获取这些相似用户评分过的电影，并根据用户评分，计算电影的兴趣值。
        #返回按兴趣值排序的前N个电影。
        # 电影兴趣值字典，{ movie:value, movie:value , ...}
        movie_val_dct = dict()
        # print(f'cur_user_movie_qs:{self.cur_user_movie_qs},type:{type(self.cur_user_movie_qs)}')
        # print(Movie.objects.all() & self.cur_user_movie_qs)
        # 用户，相似度
        for user, _ in user_lst:
            # 获取相似用户评分过的电影，并且不在前用户的评分列表中的，再加上score字段，方便计算兴趣值
            movie_set = Movie.objects.filter(user=user).exclude(id__in=self.cur_user_movie_qs).annotate(
                score=Max('movie_rating__score'))
            for movie in movie_set:
                movie_val_dct.setdefault(movie, 0)
                # 累计用户的评分
                movie_val_dct[movie] += movie.score
        print('recommend movie list calculated!')
        return sorted(movie_val_dct.items(), key=lambda x: -x[1])[:self.N]

    def get_queryset(self):
        #获取要展示的对象列表（推荐的电影列表）
        s = time.time()
        # 获得最相似的K个用户列表
        user_lst = self.get_user_sim()
        # 获得推荐电影的id
        movie_lst = self.get_recommend_movie(user_lst)
        print(movie_lst)
        result_lst = []
        for movie, _ in movie_lst:
            result_lst.append(movie)
        e = time.time()
        print(f"用时:{e - s}")
        return result_lst

    def get_context_data(self, *, object_list=None, **kwargs):
        context = super(RecommendMovieView, self).get_context_data(*kwargs)
        paginator = context.get('paginator')
        page_obj = context.get('page_obj')
        pagination_data = self.get_pagination_data(paginator, page_obj)
        context.update(pagination_data)
        return context

    def get_pagination_data(self, paginator, page_obj, around_count=2):
        current_page = page_obj.number

        if current_page <= around_count + 2:
            left_pages = range(1, current_page)
            left_has_more = False
        else:
            left_pages = range(current_page - around_count, current_page)
            left_has_more = True

        if current_page >= paginator.num_pages - around_count - 1:
            right_pages = range(current_page + 1, paginator.num_pages + 1)
            right_has_more = False
        else:
            right_pages = range(current_page + 1, current_page + 1 + around_count)
            right_has_more = True
        return {
            'left_pages': left_pages,
            'right_pages': right_pages,
            'current_page': current_page,
            'left_has_more': left_has_more,
            'right_has_more': right_has_more
        }