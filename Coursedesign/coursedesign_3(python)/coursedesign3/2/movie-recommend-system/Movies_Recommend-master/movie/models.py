
from django.db import models
from django.db.models import Avg
from django.core import validators


class Genre(models.Model):
    #种类
    name = models.CharField(max_length=100)

#指定了在数据库中使用 'Genre' 表作为模型的存储表。
    class Meta:
        db_table = 'Genre'

    def __str__(self):
        return f"<Genre:{self.name}>"


class Movie(models.Model):
    # 电影名
    name = models.CharField(max_length=256)
    # imdb_id是info文件里面的电影顺序
    imdb_id = models.IntegerField()

    # 时长
    time = models.CharField(max_length=256, blank=True)
    # 类型
    genre = models.ManyToManyField(Genre)
    # 发行时间
    release_time = models.CharField(max_length=256, blank=True)
    # 简介
    intro = models.TextField(blank=True)
    # 导演
    director = models.CharField(max_length=256, blank=True)
    # 编剧
    writers = models.CharField(max_length=256, blank=True)
    # 演员
    actors = models.CharField(max_length=512, blank=True)
    # 电影和电影之间的相似度,A和B的相似度与B和A的相似度是一致的，所以symmetrical设置为True
    movie_similarity=models.ManyToManyField("self",through="Movie_similarity",symmetrical=False)

    class Meta:
        db_table = 'Movie'

    def __str__(self):
        #模型的字符串表示方法，用于返回对象的可读性更好的字符串
        return f"<Movie:{self.name},{self.imdb_id}>"

    def get_score(self):
        # 定义一个获取平均分的方法，模板中直接调用即可
        # 格式 {'score__avg': 3.125}
        result_dct = self.movie_rating_set.aggregate(Avg('score'))
        try:
            # 只保留一位小数
            result = round(result_dct['score__avg'], 1)
        except TypeError:
            return 0
        else:
            return result

    def get_user_score(self, user):
        #返回特定用户对电影的评分
        return self.movie_rating_set.filter(user=user).values('score')

    def get_score_int_range(self):
        #返回电影评分的整数范围
        return range(int(self.get_score()))

    def get_genre(self):
        #返回与电影相关联的流派或类型列表
        genre_dct = self.genre.all().values('name')
        genre_lst = []
        for dct in genre_dct.values():
            genre_lst.append(dct['name'])
        return genre_lst

    def get_similarity(self,k=5):
        #获取与当前电影最相似的前k部电影
        # 获取5部最相似的电影的id
        similarity_movies=self.movie_similarity.all()[:k]
        print(similarity_movies)
        # movies=Movie.objects.filter(=similarity_movies)
        # print(movies)
        return similarity_movies

class Movie_similarity(models.Model):
    #通过此模型，可以方便地检索和操作电影之间的相似度信息。
    movie_source=models.ForeignKey(Movie,related_name='movie_source',on_delete=models.CASCADE)
    movie_target=models.ForeignKey(Movie,related_name='movie_target',on_delete=models.CASCADE)
    similarity=models.FloatField()
    class Meta:
        # 按照相似度降序排序
        ordering=['-similarity']

class User(models.Model):
    name = models.CharField(max_length=128, unique=True)
    password = models.CharField(max_length=256)
    email = models.EmailField(unique=True)
    rating_movies = models.ManyToManyField(Movie, through="Movie_rating")

    def __str__(self):
        return "<USER:( name: {:},password: {:},email: {:} )>".format(self.name, self.password, self.email)

    class Meta:
        db_table = 'User'


class Movie_rating(models.Model):
    # 评分的用户
    #这是一个外键字段，关联到 User 模型，表示评分的用户。on_delete=models.CASCADE 表示当关联的用户被删除时，与之关联的评分也会被级联删除。
    user = models.ForeignKey(User, on_delete=models.CASCADE, unique=False)
    # 评分的电影
    movie = models.ForeignKey(Movie, on_delete=models.CASCADE, unique=False)
    # 分数
    score = models.FloatField()
    # 评论，可选
    comment = models.TextField(blank=True)

    class Meta:
        db_table = 'Movie_rating'

class Movie_hot(models.Model):
    '''存放最热门的一百部电影'''
    # 电影外键
    #表示当关联的电影被删除时，与之关联的热门电影也会被级联删除
    movie=models.ForeignKey(Movie,on_delete=models.CASCADE)
    # 评分人数
    rating_number=models.IntegerField()
    class Meta:
        db_table='Movie_hot'
        ordering=['-rating_number']
