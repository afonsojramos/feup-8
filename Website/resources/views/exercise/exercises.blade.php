@extends('layouts.app')

@section('content')
<div class="list-group container">

    @foreach ($exercises as $exercise)

    <a href="#" class="list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4">
        <div class="d-flex w-100 justify-content-between">
            <h3 class="mb-1">{{str_limit($exercise->title, 50)}}</h3>
            <p class="mb-1">{{ $exercise->creator_name }}</p>
        </div>
        <h5>{{ $exercise->description }}</h5>
    </a>

    @endforeach
</div>

@endsection